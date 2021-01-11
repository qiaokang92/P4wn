import sys
import os
import subprocess
import time

def parse_query():

    for i in range(10):
        if not os.path.isfile("query"+str(i+1)+".txt"):
            print "Query file doesn't exist!"

    bcover = [[] for i in range(10)]
    #print bcover
    for i in range(10):
        #print 'i = '+str(i)

        f = open("query"+str(i+1)+".txt")

        for line in f.readlines():
            if line[0] == '-': # skip this unused line
                continue
            words = line.split('|')
            # print words
            if words[1] == "klee-out-"+str(i):
                #print words[5]
                bcover[i].append(words[5][4:])

    f.close()
    return bcover

if __name__ == "__main__":
    bcover = parse_query()

    for i in range(10):
        res = []
        for j in range(len(bcover[i])):
            if j%6 == 0:
                res.append(bcover[i][j])
        
        print res


    # for i in range(10):
    #     print bcover[i]