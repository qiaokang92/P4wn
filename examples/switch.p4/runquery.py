import sys
import os
import subprocess
import time

def start_query():

    for i in range(10):
        if os.path.isfile("query"+str(i+1)+".txt"):
            print "Query file exist!"

    num = 0
    while num < 1000000:
        for i in range(10):
            return_code = subprocess.call("./klee-stats klee-out-"+str(i)+" >> query"+str(i+1)+".txt", shell=True)
            if return_code != 0:
                print "query " + str(i) + "failed."
                exit(1)
        num += 1
        print "Query at num = "+str(num)+", time = " + str(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))
        time.sleep(600)


if __name__ == "__main__":
    start_query()