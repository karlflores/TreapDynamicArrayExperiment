#!/usr/bin/env python3
import subprocess
import numpy as np
from subprocess import PIPE
import matplotlib.pyplot as plt 
from multiprocessing.pool import ThreadPool
from itertools import combinations
from time import time, sleep 
import numpy as np
import sys
import argparse

'''
PYTHON PROGRAM TO RUN EXPERIMENTS

'''


class Counters:
    i = 0
    times = []

def plot(d1, d2):
    x_1 = []
    x_2 = []
    y_1 = []
    x_1_mean = []
    y_1_mean = [] 
    x_2_mean = []
    y_2 = []
    y_2_mean = []

    for keys in d1: 
        for data in d1[keys]:
            x_1.append(int(keys))
            y_1.append(data)
        x_1_mean.append(int(keys))
        y_1_mean.append(np.mean(d1[keys]))
    for keys in d2: 
        for data in d2[keys]:
            x_2.append(int(keys))
            y_2.append(data)
        x_2_mean.append(int(keys))
        y_2_mean.append(np.mean(d2[keys]))

    print("TREAP")
    for i in range(len(y_1_mean)):
        print("{} : {}".format(x_1_mean[i],y_1_mean[i]))

    print("DYNAMIC ARR")
    for i in range(len(y_2_mean)):
        print("{} : {}".format(x_2_mean[i],y_2_mean[i]))
    '''
    fig, axs = plt.subplots(1,2, constrained_layout=True)
    #axs[0].scatter(x_1,y_1);
    fig.suptitle("Experiment 1")
    axs[0].plot(x_1_mean, y_1_mean,'--o');
    axs[0].set_title("Treap")
    axs[0].set_ylabel("time (ms)")
    axs[0].set_xlabel("Number of Insertions")
    axs[0].set_ylim(bottom=0)
    #axs[1].scatter(x_2,y_2,'x',)
    axs[1].plot(x_2_mean,y_2_mean,'--o')
    axs[1].set_title("Dynamic Array")
    axs[1].set_ylabel("time (ms)")
    axs[1].set_xlabel("Number of Insertions")
    axs[1].set_ylim(bottom=0)
    plt.show()
    '''
    l1 = plt.plot(x_1_mean, y_1_mean,'--o',label="treap");
    l2 = plt.plot(x_2_mean,y_2_mean,'--x',label="dynamic array")
    plt.ylabel("time (ms)")
    plt.title("Experiment 1")
    plt.xlabel("Operation Sequence Length")
    plt.legend(loc='upper left')
    plt.ylim(bottom=0)
    plt.show()
def runAllRuns(params,threadCount=4):
    pool = ThreadPool(threadCount)
    results = pool.map(execExpr, params)
    pool.close()
    pool.join
    return results



def execExpr(param):
    #print("launching experiment")
    sleep(1)
    process = subprocess.Popen(["./ds_expr", str(param), "1"],stdout=PIPE)
    (output, err) = process.communicate()
    process.wait()
    print('Output {}\r'.format(str(output.decode("utf-8")), end='\r'))
    return param, output.decode('utf-8')

if __name__ == "__main__":

    # PROCESS THE ARGUMENTS
    parser = argparse.ArgumentParser(description='DS Experiment Testing')
    parser.add_argument('-tc', '--threadCount',
                            help='Dataset name',
                            choices=range(1,200),
                            default=1,
                            type=int)
    args = parser.parse_args()

    # generate all notes
    print("#"*42)
    print('Experiment Driver')
    print("#"*42)
    subprocess.call(["make"])
    size = [10000,20000,30000,50000,80000,100000,200000,300000,500000,600000,800000,900000,1000000,1100000,1200000,1300000,1400000,1500000]
    #size = [1,5,10,50,100]

    result_treap = {} 
    result_arr = {} 
    for s in size: 
        result_treap[str(s)] = []
        result_arr[str(s)] = []
    
    print(result_arr, result_treap) 

    sizes = []

    # lets do 100 runs of each size 
    for i in range(5): 
        [sizes.append(s) for s in size]

    print(size)
    start = time()
    output = runAllRuns(sizes,args.threadCount)
    end = time()

    # now we need to parse the output
    for s,t in output:
       t1,t2 = str(t).split(", ")
       result_treap[str(s)].append(int(t1))
       result_arr[str(s)].append(int(t2))
    
    print(result_treap, result_arr) 
    plot(result_treap, result_arr)
