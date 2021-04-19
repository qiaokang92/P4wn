#include "ModelCounter.h"
#include "klee/Expr.h"
#include <stdio.h>
#include <string>
#include <map>
#include <fstream>
#include "llvm/Support/raw_ostream.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>
#include "helper.h"
#include <chrono>
#include <json/json.h>

using namespace klee;
using namespace std;
using namespace llvm;

/************************************
******* helper functions ************
************************************/

string config_path = "/home/jiarong/P4wn/config.json";

static string GetStdoutFromCommand(string cmd)
{
   string data;
   FILE * stream;
   const int max_buffer = 4096;
   char buffer[max_buffer];
   cmd.append(" 2>&1");

   stream = popen(cmd.c_str(), "r");
   if (stream) {
      while (!feof(stream))
         if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      pclose(stream);
   }
   return data;
}

// TODO: hack LattE so that we can get the result easily
static int getCountFromOuput(string retString)
{
   // printf("extracting from === \n%s\n", retString.c_str());
   string line;
   string reg1, reg2;
   std::istringstream f(retString);
   while (getline(f, line)) {
      if (line.find("The number of lattice points is:") != std::string::npos) {
         reg1 = "(.*The number of lattice points is: )([0-9]*)(.*)";
         break;
      }
      if (line.find("The number of lattice points is ") != std::string::npos) {
         reg2 = "(.*The number of lattice points is )([0-9]*)(.*)";
         break;
      }
   }

   string count = regex_replace(line,
        std::regex(reg1 == ""? reg2 : reg1),
        std::string("$2"));

   // printf("coverting count = %s\n", count.c_str());
   if (count == "")
      return 0;
   else
      return stoi(count);
}

// Found the constant in the kquery expressions
static int find_nums(string str, int paren_count){
    string ret_str = str;
    reverse(ret_str.begin(), ret_str.end());
    for(int i = 0; i < paren_count; i++){
        ret_str = ret_str.substr(ret_str.find(")") + 1);
    }
    ret_str = ret_str.substr(0, ret_str.find(" "));
    reverse(ret_str.begin(), ret_str.end());
    return stoi(ret_str);
}


/************************************
******* LattECounter class **********
************************************/

string LattECounter::expr2Str(ref<Expr> e)
{
   string str;
   raw_string_ostream TmpStr(str);
   e.get()->print(TmpStr);
   string s = TmpStr.str();
   s.erase(remove(s.begin(), s.end(), '\n'), s.end());

   return s;
}

//The function that translate kquery format to latte format
string LattECounter::conStrs2Vex(vector<string> k)
{
    // k is the string that represents the kquery input
    // Assume there are four symbolic variables
    int cmdplc, sign, start_spc, len_spc, num_equal = 0, var_count = 1;
    vector<int> equal_tok;
    vector<int> sym_var{0};
    map<string, int> var_map;
    string latte_str = "";
    // The array containing different expression
    string bitvec[] = {"Concat", "ZExt", "SExt", "Extract"};
    string arith[] = {"Add", "Sub", "Mul"};
    string bitopt[] = {"And", "Or", "Xor", "Shl", "LShr", "AShr"};

    // Find all the symbolic variables
    for (unsigned int i = 0; i < k.size(); i++){
        string temp = k[i];
        while(temp.find("Read") != string::npos){
            temp = temp.substr(temp.find("Read") - 1);
            // cout << temp << endl;
            string temp_str = temp.substr(0, temp.find(")") + 1);
            reverse(temp_str.begin(), temp_str.end());
            // Assume the symbolic variables are one character
            string temp_var = temp_str.substr(1,temp_str.find("(") - 1);
            // cout << temp_var << endl;
            if(var_map.find(temp_var) == var_map.end()){
                sym_var.push_back(0);
                var_map[temp_var] = var_count++;
            }
            temp = temp.substr(temp.find("Read") + 4);
        }
    }

    // The map records the hierarchy of the query expressions
    map<int, string> cmd_hier;
    // Get all the tokens except the bitvec manipulation expressions
    for(unsigned int i = 0; i < k.size(); i++){
        cmd_hier.clear();
        int num_paren = 0, ind = 0;
        for (unsigned int j = 0; j < sym_var.size(); j++){
            sym_var[j] = 0;
        }
        sign = 1;
        while(k[i].find("(") < k[i].size()){
            // Add one to the number of parenthesis we found
            num_paren += 1;
            // The string now begins with the latest cmd we found
            cmdplc = k[i].find("(") + 1;
            string curcmd = k[i].substr(cmdplc, k[i].find(" ", cmdplc) - cmdplc);
            k[i] = k[i].substr(cmdplc);

            // Dealing with comparison operators
            if (curcmd == "Eq"){
                start_spc = k[i].find(" ") + 1;
                len_spc = k[i].substr(start_spc).find(" ");;
                if (k[i].substr(start_spc, len_spc) == "false"){
                    sign *= -1;
                    sym_var[0] -= 1;
                }
                else{
                    k[i] = k[i].substr(2);
                    num_equal += 1;
                    if(k[i].substr(k[i].find_first_not_of(" "), 1) == "("){
                        sym_var[0] += find_nums(k[i], num_paren);
                    }
                    else{
                        start_spc = k[i].find(" ") + 1;
                        len_spc = k[i].substr(start_spc).find(" ");
                        sym_var[0] += sign * stoi(k[i].substr(start_spc, len_spc));
                    }
                    equal_tok.push_back(i);
                }
            }
            // For <=, >=, <, and >
            if(curcmd == "Sle" || curcmd == "Sge" || curcmd == "Slt" || curcmd == "Sgt"){
                k[i] = k[i].substr(3);
                if(curcmd == "Sge" || curcmd == "Sgt"){
                    sign *= -1;
                }
                // Decides if the left/right side is the symbolic variable
                if(k[i].substr(k[i].find_first_not_of(" "), 1) == "("){
                    sym_var[0] += sign * find_nums(k[i], num_paren);
                }
                else{
                    sign *= -1;
                    start_spc = k[i].find(" ") + 1;
                    len_spc = k[i].substr(start_spc).find(" ");
                    sym_var[0] += sign * stoi(k[i].substr(start_spc, len_spc));
                }
                if(curcmd == "Slt" || curcmd == "Sgt"){
                    sym_var[0] -= 1;
                }
            }
            // For bitvector manipulationsd
            if(find(bitvec, bitvec+4, curcmd) != end(bitvec)){
                continue;
            }
            // Get the symbolic variables
            if(curcmd == "Read"){
                string temp_str = k[i].substr(0, k[i].find(")") + 1);
                reverse(temp_str.begin(), temp_str.end());
                // Assume the symbolic variables are one character
                curcmd = temp_str.substr(1,temp_str.find("("));
            }
            cmd_hier.insert(pair<int, string>(ind, curcmd));
            ind += 1;
        }
        cmd_hier[ind] = "None";


        // Change the lattE format based on the tokens we found
        for (int i = cmd_hier.size() - 1; i >= 0; i--){
            // Decide if it is a symbolic variable or an expression
            if(var_map.find(cmd_hier[i]) != var_map.end()){
                //If it is a symbolic variable, then make its coefficient 1
                sym_var[var_map[cmd_hier[i]]] = sign * 1;
                continue;
            }
            else{
                if(find(arith, arith + 3, cmd_hier[i])){
                    if(cmd_hier[i] == "Add"){
                        sym_var[var_map[cmd_hier[i+1]]] = sign;
                        sym_var[var_map[cmd_hier[i+2]]] = sign;
                        continue;
                    }
                    else if(cmd_hier[i] == "Sub"){
                        sym_var[var_map[cmd_hier[i+1]]] = sign;
                        sym_var[var_map[cmd_hier[i+2]]] = -1 * sign;
                    }
                    cmd_hier[i] = cmd_hier[i+1];
                    cmd_hier[i+1] = cmd_hier[i+3];
                    cmd_hier[i+2] = "None";
                }
            }
        }
        latte_str += to_string(sym_var[0]) + " ";
        // Print out the LattE translation
        for(unsigned int j = 1; j < sym_var.size(); j++){
            sym_var[j] *= -1;
            latte_str += to_string(sym_var[j]) + " ";
        }
        latte_str += "\n";
    }
    if(num_equal != 0){
        latte_str += "linearity " + to_string(num_equal) + " ";
        for(int tok : equal_tok){
            latte_str += to_string(tok + 1) + " ";
        }
    }
    latte_str = to_string(k.size()) + " " + to_string(sym_var.size()) + "\n" + latte_str;

    return latte_str;
}

string LattECounter::conManager2Vex(ConstraintManager cons)
{
   vector<string> conStrs;
   string ret;

   // convert ConstraintManager to an array of constraint string in kquery format
   typedef std::vector< ref<Expr> >::const_iterator constraint_iterator;
   for (constraint_iterator it = cons.begin(),
                            ie = cons.end(); it != ie; ++it) {
      ref<Expr> cond = (*it);
      string con = expr2Str(cond);
      // printf("appending %s to conStrs\n", con.c_str());
      // printf("%s\n", con.c_str());
      conStrs.push_back(con);
   }

   ret = conStrs2Vex(conStrs);
   // printf("tranlated vex = %s\n", ret.c_str());

   return ret;
}

double LattECounter::computeProb(ref<Expr> e, ConstraintManager cons)
{
   string vex1_full, vex2_full;
   double ret;

   vex2_full = conManager2Vex(cons);
   cons.addConstraint(e);
   vex1_full = conManager2Vex(cons);

   //printf("got translated vex2_full=\n%s\n", vex2_full.c_str());
   //printf("got translated vex1_full=\n%s\n", vex1_full.c_str());

   // Temporal file to store the input of LattE
   string out_file = "/tmp/matrix.txt";
   // LattE executable location
   string cmd = "count";

   cmd += " " + out_file;

   ofstream out;
   out.open(out_file);
   out << vex1_full;
   out.flush();
   out.close();

   string retString;
   retString = GetStdoutFromCommand(cmd.c_str());
   double count1 = getCountFromOuput(retString);

   out.open(out_file);
   out << vex2_full;
   out.flush();
   out.close();

   retString = GetStdoutFromCommand(cmd.c_str());
   double count2 = getCountFromOuput(retString);

   assert(count2 != 0);
   ret = count1 / count2;
   //printf("count1=%f, count2=%f, prob=%f\n", count1, count2, ret);

   assert(ret <= 1);
   assert(ret >= 0);

   return ret;
}


// Compute prob based on pre-defined MC queries
double LattECounter::computeProbByOps(string ops, string prog)
{
   LOG(-1, "computeProbByOps, ops=%s", ops.c_str());
   double ret;

   auto t1 = std::chrono::high_resolution_clock::now();

   Json::Reader reader;
   Json::Value root;

   ifstream in(config_path, ios::binary);

   if (!in.is_open())
   {
      cout << "Error opening file\n";
      assert(0);
   }

   if (!reader.parse(in, root)) {
      cout << "Read json fail"<<endl;
      assert(0);

   }

   string file1 = root["p4wn_path"].asString() + "/examples/"
                  + prog + "/" + ops + "_up.mc";
   string file2 = root["p4wn_path"].asString() + "/examples/"
                  + prog + "/" + ops + "_down.mc";

   LOG(-1, "file1=%s, file2=%s", file1.c_str(), file2.c_str());

   // LattE executable location
   string cmd = "count";

   string cmd1 = cmd + " " + file1;
   string cmd2 = cmd + " " + file2;

   string retString;
   retString = GetStdoutFromCommand(cmd1.c_str());
   double count1 = getCountFromOuput(retString);

   cout << "ddd "<<cmd2.c_str() << endl;
   retString = GetStdoutFromCommand(cmd2.c_str());
   double count2 = getCountFromOuput(retString);

   assert(count2 != 0);
   ret = count1 / count2;
   LOG(-1, "count1=%f, count2=%f, prob=%f\n", count1, count2, ret);

   assert(ret <= 1);
   assert(ret >= 0);

   LOG(-1, "computeProbByOps, ops=%s, result=%f", ops.c_str(), ret);

   auto t2 = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

   LOG(-1, "MC invoked, time %ld us", duration);

   return ret;
}
