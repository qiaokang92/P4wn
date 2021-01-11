import re
import uuid
from difflib import SequenceMatcher
# from helper import eprint

headers = []
structFieldsHeaderTypes = {} #structField, structFieldType
structs = {} # structName, listOfFields
headerStackSize = {}
currentPacketAllocationPosition = 0
emitPosition = 0
typedef = {} #typedefName, typedefNode
actionIDs = {} #actionName, nodeID
tableIDs = {} #tableName, nodeID
declarationTypes = {} #instanceName, instanceType
forwardDeclarations = []
package = ""
currentTable = "" 
forwardingRules = {}
currentTableKeys = {} #keyName, (exact, lpm or ternary)
currentTableKeysOrdered = []
currentTableDefaultAction = ""
globalDeclarations = ""
assertionsCount = 0 #tracking id for klee_print_once
finalAssertions = """void assert_error(int id, char msg[]) {
\tklee_print_once(id, msg);
\t//klee_abort();
}

void end_assertions() {
"""
emitHeadersAssertions = []
extractHeadersAssertions = []

# cleanup global variables for run() reusability in the same program...
def cleanup_variables():
    global headers
    headers = []
    global structFieldsHeaderTypes
    structFieldsHeaderTypes = {} #structField, structFieldType
    global structs
    structs = {} # structName, listOfFields
    global headerStackSize
    headerStackSize = {}
    global currentPacketAllocationPosition
    currentPacketAllocationPosition = 0
    global emitPosition
    emitPosition = 0
    global typedef
    typedef = {} #typedefName, typedefNode
    global actionIDs
    actionIDs = {} #actionName, nodeID
    global tableIDs
    tableIDs = {} #tableName, nodeID
    global declarationTypes
    declarationTypes = {} #instanceName, instanceType
    global forwardDeclarations
    forwardDeclarations = []
    global package
    package = ""
    global currentTable
    currentTable = "" 
    global forwardingRules
    forwardingRules = None
    global currentTableKeys
    currentTableKeys = {} #keyName, (exact, lpm or ternary)
    global currentTableKeysOrdered
    currentTableKeysOrdered = []
    global currentTableDefaultAction
    currentTableDefaultAction = ""
    global globalDeclarations
    globalDeclarations = ""
    global assertionsCount
    assertionsCount = 0 #tracking id for klee_print_once
    global finalAssertions
    finalAssertions = """void assert_error(int id, char msg[]) {
    \tklee_print_once(id, msg);
    \t//klee_abort();
    }

    void end_assertions() {
    """
    global emitHeadersAssertions
    emitHeadersAssertions = []
    global extractHeadersAssertions
    extractHeadersAssertions = []

def remove_unecessary_extract_aux_vars(lines):
    returnString = ""
    global_vars = set()
    for line in lines:
        if "int extract_header_" in line:
            header = line.split(" ")[1][15:]
            if not (header in global_vars):
                global_vars.add(header)
                returnString += line + "\n"
        elif "[POST]" in line:
            header = line.split(" ")[0][22:]
            if header in global_vars:
                returnString += "\t" + line[7:] + "\n"
        else:
            returnString += line + "\n"
    return returnString

def post_processing(model_string):
    return remove_unecessary_extract_aux_vars(model_string.split("\n"))

def run(node, rules):
    cleanup_variables()
    if rules != None:
        global forwardingRules
        forwardingRules = rules
    returnString = "#define BITSLICE(x, a, b) ((x) >> (b)) & ((1 << ((a)-(b)+1)) - 1)\n#include<stdio.h>\n#include<stdint.h>\n#include<stdlib.h>\n\nint assert_forward = 1;\nint action_run;\n\nvoid end_assertions();\n\n"
    program = toC(node)
    returnString += globalDeclarations
    for declaration in forwardDeclarations:
        returnString += "\nvoid " + declaration[0] + "(" + declaration[1] + ");"
    returnString += "\n\n" + program + finalAssertions + "}\n\n"
    return returnString
    

def toC(node):
    # test for annotations
    returnString = ""
    if hasattr(node, "annotations"):
        returnString += Annotations(node.annotations)
    if 'Vector' in node.Node_Type:
        for v in node.vec:
            #returnString += "<<" + str(v.Node_ID) + ">>"
            nodeString = toC(v)
            if nodeString != "":
                returnString += nodeString + "\n"
    else:
        returnString += globals()[node.Node_Type](node) #calls corresponding type function according to node type
    return returnString

########### TYPE FUNCTIONS ###########

def P4Program(node):
    return toC(node.declarations)

def P4Control(node):
    returnString = "//Control\n"
    actions = ""
    tables = ""
    for local in node.controlLocals.vec:
        if local.Node_Type == "Declaration_Variable" or local.Node_Type == "Declaration_Instance":
            nodeString = toC(local)
            if nodeString != "":
                returnString += nodeString + "\n"
        elif local.Node_Type == "P4Action":
            actions += toC(local) + "\n"
        elif local.Node_Type == "P4Table":
            tables += toC(local) + "\n"
    returnString += "\nvoid " + node.name + "() {\n\t"
    for v in node.body.components.vec:
        returnString += toC(v) + "\n\t"
    if len(node.body.components.vec) > 0:
        returnString = returnString[:-2]
    returnString += "\n}\n\n"
    returnString += actions
    returnString += tables
    return returnString

def Cmpl(node):
    return "~" + toC(node.expr) 

def BlockStatement(node):
    returnString = ""
    for v in node.components.vec:
        nodeString = toC(v)
        if nodeString != "":
            returnString += "\t" + nodeString + "\n"
    return returnString

# precedence of operators require anoter set of parenthesis
def BAnd(node):
    return "(" + toC(node.left) + " & " + toC(node.right) + ")"

def BOr(node):
    return "(" + toC(node.left) + " | " + toC(node.right) + ")"

def BXor(node):
    #return "<BXor>" + str(node.Node_ID)
    return "(" + toC(node.left) + " ^ " + toC(node.right) + ")"

def Cast(node):
    return cast(node.expr, node.destType)

def Geq(node):
    return toC(node.left) + " >= " +  toC(node.right)

def Leq(node):
    return toC(node.left) + " <= " +  toC(node.right)

def LAnd(node):
    return toC(node.left) + " && " + toC(node.right)

def LOr(node):
    return toC(node.left) + " || " + toC(node.right)

def Slice(node):
    value = toC(node.e0)
    m = toC(node.e1)
    l = toC(node.e2)
    return "BITSLICE("+ value + ", " + m + ", " + l + ")"

def Shl(node):
    return toC(node.left) + " << " +  toC(node.right)

def Shr(node):
    return toC(node.left) + " >> " +  toC(node.right)

def Mul(node):
    return str(toC(node.left)) + " * " + str(toC(node.right))

def ActionList(node):
    if forwardingRules == None:
        return actionListNoRules(node)
    else:
        return ""

def ActionListElement(node):
    #return "<ActionListElement>" + str(node.Node_ID) 
    return ""

def Add(node):
    return add(node)

def Sub(node):
    return sub(node)

def Annotation(node):
    #return "<Annotation>" + str(node.Node_ID) 
    return ""

def Annotations(node):
    returnString = ""
    for annotation in node.annotations.vec:
        if annotation.name == "assert":
            assert_string = annotation.expr.vec[0].value
            assertionResults = assertion(assert_string, annotation.expr.vec[0].Node_ID)
            returnString += assertionResults[0]
            #if assert_string[1] != "":
            #    message = assert_string[1] + "\\n"
            global finalAssertions
            global assertionsCount
            finalAssertions += "\tif (!({0}))\n\t\tassert_error({1}, \"Assertion error: {0}\");\n".format(assertionResults[1], assertionsCount)
            assertionsCount += 1
    return returnString

def assertion(assertionString, nodeID):
    returnString = ""
    logicalExpression = ""
    # errorMessage = ""
    global globalDeclarations
    if "!" == assertionString[0]:
        neg = assertion(assertionString[1:], nodeID)
        returnString += neg[0]
        logicalExpression = "!" + neg[1]
    elif "if(" == assertionString[:3]: #TODO: finish this
        ifExpression = assertionString[assertionString.find("(")+1:assertionString.rfind(")")]
        ifParameters = re.split(r',\s*(?![^()]*\))', ifExpression)
        left = assertion(ifParameters[0], nodeID)
        returnString += left[0]
        right = assertion(ifParameters[1], nodeID)
        returnString += right[0]
        logicalExpression = "!(" + left[1] + ") || (" + right[1] + ")"
    elif "&&" in assertionString:
        andParameters = assertionString.split(" && ")
        left = assertion(andParameters[0], nodeID)
        right = assertion(andParameters[1], nodeID)
        returnString += left[0]
        returnString += right[0]
        logicalExpression = "(" + left[1] + ") && (" + right[1] + ")"
    elif "==" in assertionString:
        equalityParameters = assertionString.split("==")
        left = equalityParameters[0]
        right = equalityParameters[1]
        globalVarName =  left.replace(".", "_")[:-1] + "_eq_" + right.replace(".", "_")[-1:] + "_" + str(nodeID)
        # global globalDeclarations
        globalDeclarations += "\n int " + globalVarName + ";\n"
        logicalExpression = globalVarName
        returnString += globalVarName + " = (" + left + " == " + right + ");\n\t"
    elif "<" in assertionString:
        equalityParameters = assertionString.split("<")
        left = equalityParameters[0]
        right = equalityParameters[1]
        globalVarName =  left.replace(".", "_")[:-1] + "_le_" + right.replace(".", "_")[-1:] + "_" + str(nodeID)
        # global globalDeclarations
        globalDeclarations += "\n int " + globalVarName + ";\n"
        logicalExpression = globalVarName
        returnString += globalVarName + " = (" + left + " < " + right + ");\n\t"
    elif "constant" in assertionString:
        constantVariable = assertionString[assertionString.find("(")+1:assertionString.rfind(")")]
        globalVarName = "constant_" + constantVariable.replace(".", "_") + "_" + str(nodeID)
        constantType = "uint64_t"#TODO: get proper field type
        # global globalDeclarations
        globalDeclarations += "\n" + constantType + " " + globalVarName + ";\n"
        logicalExpression =  globalVarName + " == " + constantVariable
        returnString += globalVarName + " = " + constantVariable + ";"
    elif "extract" in assertionString: #TODO: assign variable to true when extract field in model
        headerToExtract = assertionString[assertionString.find("(")+1:assertionString.rfind(")")].replace(".", "_")
        globalVarName = "extract_header_" + headerToExtract
        # global globalDeclarations
        globalDeclarations += "\nint " + globalVarName + " = 0;\n"
        logicalExpression =  globalVarName
    elif "emit" in assertionString:
        headerToEmit = assertionString[assertionString.find("(")+1:assertionString.rfind(")")].replace(".", "_")
        headerToEmitNoHeaderStack = headerToEmit.replace("[", "").replace("]", "")
        globalVarName = "emit_header_" + headerToEmitNoHeaderStack
        emitHeadersAssertions.append(headerToEmit)
        # global globalDeclarations
        globalDeclarations += "\nint " + globalVarName + " = 0;\n"
        logicalExpression = globalVarName
    elif "forward" in assertionString:
        logicalExpression = "assert_forward"
    elif "traverse" in assertionString:
        #traverseParameter = assertionString[assertionString.find("(")+1:assertionString.rfind(")")]
        globalVarName = "traverse_" + str(nodeID)
        # global globalDeclarations
        globalDeclarations += "int " + globalVarName + " = 0;\n"
        logicalExpression = globalVarName
        #if traverseParameter:
        #    #TODO: add globalVarName + " = 1;" to the parameter location
        #    pass
        #else:
        returnString += globalVarName + " = 1;"
    else:
        globalVarName = assertionString.replace(".", "_") + "_" + str(nodeID)
        # global globalDeclarations
        globalDeclarations += "\nint " + globalVarName + ";\n"
        returnString += globalVarName + " = (" + assertionString + " == 1);\n\t"
        logicalExpression = globalVarName
    return (returnString, logicalExpression)

def ArrayIndex(node):
    return toC(node.left) + "[" + str(node.right.value) + "]"

def AssignmentStatement(node):
    if isExternal(node.right):
        symValue = toC(node.left)
        return klee_make_symbolic(symValue)
    return assign(node)

def BoolLiteral(node):
    if node.value == True:
        return "1"
    else:
        return "0"

def Constant(node):
    return str(node.value)

def ConstructorCallExpression(node):
    #return "<ConstructorCallExpression>" + str(node.Node_ID)
    return "" 

def Declaration_Instance(node):
    returnString = ""
    if node.name == "main":
        if package == "V1Switch":
            parser = node.arguments.vec[0].type.path.name if hasattr(node.arguments.vec[0].type, "path") else node.arguments.vec[0].type.name
            ingress = node.arguments.vec[2].type.path.name if hasattr(node.arguments.vec[2].type, "path") else node.arguments.vec[2].type.name
            egress = node.arguments.vec[3].type.path.name if hasattr(node.arguments.vec[3].type, "path") else node.arguments.vec[3].type.name
            deparser = node.arguments.vec[5].type.path.name if hasattr(node.arguments.vec[5].type, "path") else node.arguments.vec[5].type.name
            returnString += "int main() {\n\t" +  parser + "();\n\t" + ingress + "();\n\t" + egress + "();\n\t" + deparser +  "();\n\tend_assertions();\n\treturn 0;\n}\n"
        elif package == "VSS":
            parser = node.arguments.vec[0].type.path.name if hasattr(node.arguments.vec[0].type, "path") else node.arguments.vec[0].type.name
            ingress = node.arguments.vec[1].type.path.name if hasattr(node.arguments.vec[1].type, "path") else node.arguments.vec[1].type.name
            deparser = node.arguments.vec[2].type.path.name if hasattr(node.arguments.vec[2].type, "path") else node.arguments.vec[2].type.name
            returnString += "int main() {\n\t" +  parser + "();\n\t" + ingress + "();\n\t" + deparser + "();\n\tend_assertions();\n\treturn 0;\n}\n"
    elif hasattr(node.type, "path"):
        declarationTypes[node.name] = node.type.path.name
    return returnString        
    
def Declaration_Variable(node):
    if node.type.Node_Type == "Type_Bits":
        return bitsSizeToType(node.type.size) + " " + node.name + ";"
    elif node.type.Node_Type == "Type_Boolean":
        return "uint8_t " + node.name + ";"
    elif node.type.Node_Type == "Type_Name":
        return node.type.path.name + " " + node.name + ";"
    return allocate(node)

def EmptyStatement(node):
    #return "<EmptyStatement>" + str(node.Node_ID)
    return ""

def Neq(node):
    return "(" + toC(node.left) +  " != " + toC(node.right) + ")"

def Equ(node):
    return "(" + toC(node.left) +  " == " + toC(node.right) + ")"

def ExpressionValue(node):
    return toC(node.expression) 

def Grt(node):
    return greater(node)

def IfStatement(node):
    return ifStatement(node)

def Key(node):
    returnString = "\t// keys: "
    for key in node.keyElements.vec:
        keyName = toC(key.expression)
        matchType = toC(key.matchType)
        currentTableKeys[keyName] = matchType
        currentTableKeysOrdered.append(keyName)
        returnString += keyName +  ":" + matchType + ", "
    return returnString[:-2]

def LNot(node):
    return "!" + toC(node.expr)

def Member(node):
    if node.member != 'apply':
        if node.member == "last":
            nodeName = toC(node.expr)
            return nodeName + "[" + nodeName + "_index - 1]"
        else:
            return toC(node.expr) + "." + node.member
    else:
        nodeName = toC(node.expr)
        if nodeName in tableIDs.keys():
            return nodeName + "_" + str(tableIDs[nodeName])
        elif nodeName in declarationTypes.keys():
            return declarationTypes[nodeName]
        else:
            return nodeName

def Method(node):
    if node.name == "mark_to_drop": #V1 specific
        return mark_to_drop()
    else:
        return toC(node.type)

def generatePushFront(node):
    returnString = ""
    count = toC(node.arguments.vec[0])
    hdr = toC(node.method)[:-11]
    returnString += "//push_front(" + count + ")\n"
    returnString += "\tint header_stack_size = sizeof(" + hdr + ")/sizeof(" + hdr + "[0]);\n\t"
    returnString += "int i;\n\t"
    returnString += "for (i = header_stack_size - 1; i >= 0; i -= 1) {\n\t\t"
    returnString += "if (i >= " + count + ") {\n\t\t\t"
    returnString += hdr + "[i] = " + hdr + "[i-" + count + "];\n\t\t"
    returnString += "} else {\n\t\t"
    returnString += hdr + "[i].isValid = 0;\n\t}\n}\n\t"
    returnString += hdr + "_index = " + hdr + "_index + " + count + ";\n\t"
    returnString += "if (" + hdr + "_index > header_stack_size) " + hdr + "_index = header_stack_size;\n"
    return returnString

def MethodCallExpression(node):
    returnString = ""
    if hasattr(node.method, 'member') and node.method.member == "push_front":
        returnString += generatePushFront(node)
    elif hasattr(node.method, 'member') and node.method.member == "extract":
        returnString += extract(node)
    elif hasattr(node.method, 'member') and node.method.member == "emit":
        returnString += emit(node)
     # execute meter, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'member') and node.method.member == "execute_meter":
        returnString += klee_make_symbolic(toC(node.arguments.vec[1]))
    # read register, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'member') and node.method.member == "read":
        returnString += klee_make_symbolic(toC(node.arguments.vec[0]))
    # write register, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'member') and node.method.member == "write":
        #ignore it
        pass
    # clone3, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'path') and node.method.path.name == "clone3":
         #ignore it
        pass
    # count, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'member') and node.method.member == "count":
         #ignore it
        pass
    # count, TODO: separate this into an 'extern methods' method
    elif hasattr(node.method, 'path') and node.method.path.name == "hash":
         returnString += klee_make_symbolic(toC(node.arguments.vec[0]))
    # extern method: Name it as extern for later processing
    elif hasattr(node.method, 'expr') and node.method.expr.type.Node_Type == "Type_Extern":
        returnString +=  "//Extern: " + toC(node.method)
    #verify method
    elif hasattr(node.method, 'path') and node.method.path.name == "verify":
        returnString += "if(!(" + toC(node.arguments.vec[0]) + ")) {\n"
        returnString += "\t\tend_assertions();\n\t\texit(1);\n\t}\n"
     #SetValid method
    elif hasattr(node.method, 'member') and node.method.member == "setValid":
        returnString += toC(node.method.expr) + ".isValid = 1;"
     #SetInvalid method
    elif hasattr(node.method, 'member') and node.method.member == "setInvalid":
        returnString += toC(node.method.expr) + ".isValid = 0;"
    elif hasattr(node.method, 'path') and node.method.path.name == "random":
        field = toC(node.arguments.vec[0])
        returnString += "//random\n\t"
        returnString += klee_make_symbolic(field)
        lowerBound = toC(node.arguments.vec[1])
        upperBound = toC(node.arguments.vec[2])
        returnString += "\n\tklee_assume(" + field + " > " + lowerBound + " && " + field + " < " + upperBound + ");"
    elif hasattr(node.method, 'path') and node.method.path.name == "digest":
        pass
    else:
        # Special treatment for "isValid" calls
        # isValid is modeled as an uint8_t instead of a function!
        if hasattr(node.method, 'member') and node.method.member == "isValid":
            returnString = toC(node.method)
        else:
            returnString = toC(node.method) + "();"

    return returnString

def MethodCallStatement(node):
    return toC(node.methodCall)

def NameMapProperty(node):
    #return "<NameMapProperty>" + str(node.Node_ID)
    return ""

def P4Action(node):
    actionIDs[node.name] = node.Node_ID
    actionData = "action_run = " + str(node.Node_ID) + ";\n\t"
    parameters = ""
    for param in node.parameters.parameters.vec:
        if param.direction == "":
            if forwardingRules != None:
                parameter = ""
                if param.type.Node_Type == "Type_Bits":
                    parameter = bitsSizeToType(param.type.size) + " " + param.name
                else:
                    parameter = toC(param.type) + " " + param.name 
                parameters += parameter + ", "
            else:
                if param.type.Node_Type == "Type_Bits":
                    actionData += bitsSizeToType(param.type.size) + " " + param.name + ";\n"
                else:
                    actionData += toC(param.type) + " " + param.name + ";\n"
                actionData += klee_make_symbolic(param.name)

    #Remove comma after last parameter
    if parameters != "":
        parameters = parameters[:-2]

    forwardDeclarations.append([node.name + "_" + str(node.Node_ID), parameters])

    actionName = node.name + "_" + str(node.Node_ID)
    return "// Action\nvoid " + actionName + "(" + parameters + ") {\n\t" + actionData + toC(node.body) + "\n}\n\n"

def P4Table(node):
    #print "\nTable " + str(node.name)
    tableIDs[node.name] = node.Node_ID
    global currentTable
    currentTable = node.name
    forwardDeclarations.append([node.name + "_" + str(node.Node_ID), ""])
    tableBody = toC(node.properties)
    if forwardingRules != None:
        tableBody = actionListWithRules(node)
    global currentTableKeys
    currentTableKeys = {}
    global currentTableKeysOrdered
    currentTableKeysOrdered = []
    global currentTableDefaultAction
    currentTableDefaultAction = ""
    tableName = node.name + "_" + str(node.Node_ID)
    return "//Table\nvoid " + tableName + "() {\n" + tableBody + "\n}\n\n"

def ParameterList(node):
    returnString = ""
    for parameter in node.parameters.vec:
        returnString += allocate(parameter) + ",\n\t"
    return returnString

def Path(node):
    return node.name

def PathExpression(node):
    return toC(node.path)

def Property(node):
    if node.name == "default_action":
        global currentTableDefaultAction
        currentTableDefaultAction = toC(node.value)
        return "\t// default_action " + currentTableDefaultAction
    elif node.name == "size":
        return "\t// size " + toC(node.value)
    elif node.name == "actions":
        return toC(node.value)
    elif node.name == "key":
        return toC(node.value)
    else:
        return ""

def SelectExpression(node):
    expressions = node.select.components.vec
    exp = []
    for expression in expressions:
        if expression.Node_Type == 'Slice':
            exp.append(Slice(expression))
        elif expression.Node_Type == 'Member':
            exp.append(toC(expression.expr) + "." + expression.member)
        elif  expression.Node_Type == "MethodCallStatement":
            if expression.method.member == "isValid":
                exp.append(expression.method.expr.path.name + ".isValid")
        elif expression.Node_Type == 'Cast':
            exp.append(cast(expression.expr, expression.destType))
        elif expression.Node_Type == 'PathExpression':
             exp.append(toC(expression.path))

    cases = node.selectCases.vec
    returnString = select(cases, exp)
    return returnString

def select(cases, exp):
    returnString = ""
    for case in cases:
        fullExpression = ""
        for idx,e in enumerate(exp):
            #get apropriate case depending if select has multiple arguments or not
            if hasattr(case.keyset, 'components'):
                node = case.keyset.components.vec[idx]
            else:
                node = case.keyset

            if node.Node_Type == "Mask":
                a = toC(node.left)
                b = toC(node.right)
                fullExpression += "((" + str(e) + " & " + b + ") == (" + a + " & " + b + ")) && "
            elif node.Node_Type == 'Constant':
                fullExpression += "(" + str(e) + " == " + str(node.value) + ") && "
        if fullExpression != "":
            returnString += "if(" + fullExpression[:-4] + ")"
        returnString += "{\n\t\t" + case.state.path.name + "();\n\t} else "
    return returnString[:-6]

def StringLiteral(node):
    #return "<StringLiteral>" + str(node.Node_ID)
    return ""

def StructField(node):
    returnString = ""
    #warning: two headers defined in different structs
    #with the same name but different types would break this
    #future solution: discriminate by struct name
    if node.type.Node_Type == "Type_Name":
        structFieldsHeaderTypes[node.name] = node.type.path.name
        returnString += "\t" + structFieldsHeaderTypes[node.name] + " " + node.name + ";"
    elif node.type.Node_Type == "Type_Stack":
        structFieldsHeaderTypes[node.name] = node.type.elementType.path.name
        headerStackSize[node.name] = node.type.size.value
        returnString += "\tint " + node.name + "_index;\n"
        returnString += "\t" + structFieldsHeaderTypes[node.name] + " " + node.name + "[" + str(node.type.size.value) + "];"
    elif node.type.Node_Type == "Type_Bits":
        #TODO: model fields with more than 64 bits properly
        if node.type.size > 64:
            node.type.size = 64
        returnString += "\t" + bitsSizeToType(node.type.size) + " " + node.name + " : " + str(node.type.size) + ";"
    return returnString

def SwitchCase(node):
    return toC(node.statement)

def SwitchStatement(node):
    returnString = ""
    if node.expression.member == "action_run":
        returnString += toC(node.expression.expr) + "\n\t"
        defaultCase = None
        for case in node.cases.vec:
            if case.label.Node_Type != "DefaultExpression":
                returnString += "if(action_run == " + str(actionIDs[toC(case.label)]) + ") {\n\t\t " + toC(case) + "\n\t} else "
            else:
                defaultCase = toC(case)
        if defaultCase:
            returnString += "{\n\t\t" + defaultCase + "\n\t}"
        else:
            returnString = returnString[:-6]

    else:
        switchCases = toC(node.cases).replace("\n", ",")
        returnString = "Fork(InstructionBlock(), " + switchCases[:-1] + ")"
    return returnString

def TableProperties(node):
    return toC(node.properties)

def TypeParameters(node):
    #return "<TypeParameters>" + str(node.Node_ID)
    return ""

def Type_Action(node):
    #return "<Type_Action>" + str(node.Node_ID)
    return ""

def Type_ActionEnum(node):
    #return "<Type_ActionEnum>" + str(node.Node_ID)
    return ""

def Type_Control(node):
    #return "<Type_Control>" + str(node.Node_ID)
    return ""

def Type_Method(node):
    #return "<Type_Method>" + str(node.Node_ID)
    return ""

def Type_Name(node):
    return toC(node.path)

def TypeNameExpression(node):
    #return "<TypeNameExpression>" + str(node.Node_ID)
    return ""

def Type_Package(node):
    global package
    package = node.name
    return ""

def Type_Struct(node):
    structs[node.name] = node.fields.vec
    returnString = "typedef struct {\n"
    returnString += toC(node.fields)
    returnString += "} " + node.name + ";\n"
    return returnString

def Type_Table(node):
    return toC(node.table)

def Type_Typedef(node):
    typedef[node.name] = node
    return "typedef " + bitsSizeToType(node.type.size) + " " + node.name + ";\n"
    
def Type_Unknown(node):
    #return "<Type_Unknown>" + str(node.Node_ID)
    return ""

def Type_Error(node):
    #return "<Type_Error>" + str(node.Node_ID)
    return ""

def Type_Extern(node):
    return ""

def Declaration_MatchKind(node):
    #return "<Declaration_MatchKind>" + str(node.Node_ID)
    return ""

def Type_Header(node):
    #not sure if it remains
    fields = []
    for field in node.fields.vec:
        fields.append(field)
    headerTuple = (node.name, fields)
    headers.append(headerTuple)
    ####
    returnString = "typedef struct {\n\tuint8_t isValid : 1;\n"
    for field in node.fields.vec:
        if field.type.Node_Type == "Type_Bits":
            #TODO: model fields with more than 64 bits properly
            if field.type.size > 64:
                field.type.size = 64
            if field.name != "$valid$":
                returnString += "\t" + bitsSizeToType(field.type.size) + " " + field.name + " : " + str(field.type.size) + ";\n"
        else:
            typeName = toC(field.type)
            returnString += "\t" + typeName + " " + field.name + ": " + str(typedef[typeName].type.size) + ";\n"
    returnString += "} " + node.name + ";\n"
    return returnString

def P4Parser(node):
    returnString = declareParameters(node)
    for l in node.parserLocals.vec:
        returnString += toC(l) + "\n"
    returnString += "\n" + toC(node.states)
    returnString += "void " + node.name + "() {\n"
    returnString += SymbolizeParameters(node)
    returnString += "\tstart();\n}\n"
    return returnString 

def Type_Enum(node):
    #return "<Type_Enum>" + str(node.Node_ID)
    return ""

def Type_Parser(node):
    #return "<Type_Parser>" + str(node.Node_ID)
    return ""

def dropPacketCode():
    return "assert_forward = 0;\n\tend_assertions();\n\texit(0);"

def ParserState(node):
    components = ""
    for v in node.components.vec:
        components = components + "\t" + toC(v) + "\n"
    expression = ""
    if hasattr(node, 'selectExpression'):
        expression += toC(node.selectExpression)
        if "\n" not in expression:
            expression += "();" #it is not a select, thus it is a direct parser state transition
    if node.name == "reject":
        expression += dropPacketCode()
    forwardDeclarations.append([node.name, ""])
    parser = "void " + node.name + "() {\n" + components + "\t" + expression + "\n}\n\n"
    return parser

    # returnString = "val parserState_" + node.name + " = InstructionBlock(\n" + toC(node.components) + ")\n"
    # return returnString

########### HELPER FUNCTIONS ###########

def actionListWithRules(node):
    #forwardingRules
    returnString = ""

    global currentTable
    backupName = currentTable
    if currentTable in forwardingRules.keys():
        pass
    elif currentTable[1:] in forwardingRules.keys():
        currentTable = currentTable[1:]
    elif currentTable[1:-2] in forwardingRules.keys():
        currentTable = currentTable[1:-2]

    # this default action string will be informat of "<action>();" 
    # as per function "Property", so we are removing the "();" part
    # TODO: this is probably not the best way to handle this situation
    defaultAction = getActionFullName(currentTableDefaultAction[:-3])
    if defaultAction == "UNKNOWN_ACTION":
        defaultAction = ""

    table_add = False

    if currentTable in forwardingRules.keys():
        # processing rules for this table
        for rule in forwardingRules[currentTable]:
            # adding entry to table
            if rule[0] == "table_add":
                match = ""
                
                for idx in range(len(currentTableKeysOrdered)):
                    key = currentTableKeysOrdered[idx]
                    if currentTableKeys[key] == "exact":
                        match += key + " == " + convertCommandValue(rule[2][idx]) + " && "
                        table_add = True
                    else:
                        #TODO: Model other match types (i.e., ternary, lpm, etc) as well as rule priorities
                        pass

                match = match[:-3]
                arguments = ""
                for arg in rule[3]:
                    arguments += convertCommandValue(arg) + ", "
                arguments = arguments[:-2]
                returnString += "\tif(" + match + "){\n\t\t" + getActionFullName(rule[1]) + "(" + arguments + ");\n\t} else "
            # changing default action
            elif rule[0] == "table_set_default":
                defaultAction = getActionFullName(rule[1])

        # finally, adding default rule
        if table_add:
            returnString += "{\n\t\t" + defaultAction + "(); // default action\n\t}\n"
        else:
            returnString += "\t" + defaultAction + "(); // default action"

    # no forwarding rules, add only default
    else:
        returnString = "\t" + defaultAction + "(); // default action"

    currentTable = backupName

    return returnString

def convertCommandValue(arg):
    if ":" in arg:
        return str(int(arg.translate(None, ":"), 16))
    elif "." in arg: #Convert IP to uint_32
        octets = arg.split(".")
        binaryRep = ""
        for octet in octets:
            binaryRep += str('{0:08b}'.format(int(octet)))
        intRep = int(binaryRep, 2)
        return str(intRep)
    else:
        return arg

def getActionFullName(actionName):
    # actionName = actionName + "_"

    check_similarity = lambda a,b: SequenceMatcher(None, a, b).ratio() 

    curr_action = "UNKNOWN_ACTION"
    similarity = 0.0

    # TODO: select the *correct* action (e.g. more than one action with the same name...)
    for action in actionIDs:
        if actionName in action:
            new_sim = check_similarity(actionName, action)
            if similarity < new_sim:
                curr_action = action
                similarity = new_sim

                if similarity > 0.9:
                    # print actionName, curr_action, similarity, 'early return'
                    return action + "_" + str(actionIDs[action])
    
    # print actionName, curr_action, similarity

    if curr_action != "UNKNOWN_ACTION":
        return curr_action + "_" + str(actionIDs[curr_action])
    else:
        return "UNKNOWN_ACTION"

def actionListNoRules(node):
    returnString = "\tint symbol;\n" + klee_make_symbolic("symbol")
    returnString += "\tswitch(symbol) {\n"
    for idx,action in enumerate(node.actionList.vec):
        if idx == len(node.actionList.vec) - 1:
            returnString += "\t\tdefault: "
        else:
            returnString += "\t\tcase " + str(idx) + ": "
        if action.expression.Node_Type == "PathExpression":
            returnString += action.expression.path.name + "_" + str(actionIDs[action.expression.path.name]) + "(); "
        elif action.expression.Node_Type == "MethodCallExpression":
            returnString += action.expression.method.path.name + "_" + str(actionIDs[action.expression.method.path.name]) + "(); "
        else:
            returnString += "ERROR:UNKNOWN ACTION LIST TYPE"
        returnString += "break;\n"
    returnString += "\t}"
    return returnString

def SymbolizeParameters(node):
    returnString = ""
    for param in node.type.applyParams.parameters.vec:
        if (param.direction == "out" or param.direction == "inout") and param.type.Node_Type == 'Parameter':
            returnString += klee_make_symbolic(param.type.name)
        if (param.direction == "out" or param.direction == "inout") and param.type.Node_Type == 'Type_Name':
            returnString += klee_make_symbolic(param.name)
    return returnString + "\n"

def declareParameters(node):
    returnString = ""
    for param in node.type.applyParams.parameters.vec:
        if (param.direction == "out" or param.direction == "inout") and param.type.Node_Type == 'Parameter':
            returnString += declareParameter(param.type)
        if (param.direction == "out" or param.direction == "inout") and param.type.Node_Type == 'Type_Name':
            returnString += declareParameter(param)
    return returnString + "\n"

def declareParameter(param):
    return param.type.path.name + " " + param.name + ";\n"

def ifStatement(node):
    condition = ""
    returnString = ""
    condition = str(toC(node.condition))
    returnString = "if(" + condition + ") {\n\t" + str(toC(node.ifTrue)) + "\n}"
    if hasattr(node, "ifFalse"):
        returnString += " else {\n\t" + str(toC(node.ifFalse)) + "\n}"
    return returnString


def greater(node):
    return str(toC(node.left)) + " > " + str(toC(node.right))

def add(node):
    return formatATNode(node.left) + " + " + formatATNode(node.right)

def sub(node):
    return formatATNode(node.left) + " - " + formatATNode(node.right)

def allocate(node):
    return "Allocate(\"" + node.name + "\")"

def assign(node):
    return str(toC(node.left)) + " = " + str(toC(node.right)) + ";"

def formatATNode(node):
    value = ""
    if node.Node_Type == 'Cast':
        value = formatATNode(node.expr)
    else:
        value = str(toC(node))
    return value

def isExternal(node):
    # the variable could be external or inside an external variable
    return "//Extern" in toC(node)

def getHeaderType(headerName):
    return structFieldsHeaderTypes[headerName]

def emit(node):
    returnString = ""
    hdrName = toC(node.arguments.vec[0])
    returnString += "//Emit " + hdrName + "\n\t"
    headerName = ""
    if node.arguments.vec[0].Node_Type == "ArrayIndex":
        headerName = node.arguments.vec[0].left.member
    else:
        headerName = hdrName.split(".")[1]
    for emitAssertion in emitHeadersAssertions:
        if headerName in emitAssertion:
            headerNameNoHeaderStack = emitAssertion.replace("[", "").replace("]", "")
            returnString += "emit_header_" + headerNameNoHeaderStack + " = " + emitAssertion + ".isValid;\n\t"

    global emitPosition
    for header in headers:
        if header[0] == getHeaderType(headerName):
            for field in header[1]:
                size = typedef[field.type.path.name].type.size if field.type.Node_Type == "Type_Name" else field.type.size
                if hdrName.split(".")[1] in headerStackSize.keys():
                    for idx in range(headerStackSize[hdrName.split(".")[1]]):
                        # global emitPosition
                        emitPosition += size
                else:
                    # global emitPosition
                    emitPosition += size
    return returnString

def extract(node):
    returnString = ""
    headerToExtract = toC(node.arguments.vec[0])
    returnString += "//Extract " + headerToExtract + "\n\t"
    if headerToExtract.endswith(".next"): # parsing a header stack
        headerToExtract = headerToExtract[:-5]
        returnString += headerToExtract + "[" + headerToExtract + "_index]" + ".isValid = 1;\n\t"
        returnString += headerToExtract + "_index++;"
    else: 
        returnString += headerToExtract + ".isValid = 1;\n\t"
        returnString += "[POST]extract_header_" + headerToExtract.replace(".", "_") + " = 1;"
    return returnString

def cast(expr, toType):
    returnString = ""
    if toType.Node_Type == "Type_Bits":
        returnString += "(" + bitsSizeToType(toType.size) + ") "
    return returnString + toC(expr)

def bitsSizeToType(size):
    if size <= 8:
        return "uint8_t"
    elif size <= 32:
        return "uint32_t"
    #elif size <= 64:
    else:
        return "uint64_t"
    #else:
    #    return "???"

def klee_make_symbolic(var):
    returnString = ""
    if "." in var:
        symbolic_name = "t" + str(uuid.uuid4()).replace("-", "_")
        returnString += "\n\tuint64_t "+ symbolic_name + ";\n"
        returnString += "\tklee_make_symbolic(&" + symbolic_name + ", sizeof(" + symbolic_name + "), \"" + symbolic_name + "\");\n\t"
        returnString += var + " = " + symbolic_name + ";\n"
    else:
        returnString += "\tklee_make_symbolic(&" + var + ", sizeof(" + var + "), \"" + var + "\");\n"
    return returnString

# ---- V1 specific ----

def mark_to_drop():
    return "void mark_to_drop() {\n\t" + dropPacketCode() + "\n}\n"


