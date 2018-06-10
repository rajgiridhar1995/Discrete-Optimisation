#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
from collections import namedtuple
Item = namedtuple("Item", ['index', 'value', 'weight'])

def solve_it(input_data):
    # Modify this code to run your optimization algorithm

    # parse the input
    lines = input_data.split('\n')

    firstLine = lines[0].split()
    item_count = int(firstLine[0])
    capacity = int(firstLine[1])

    items = []

    for i in range(1, item_count+1):
        line = lines[i]
        parts = line.split()
        items.append(Item(i-1, int(parts[0]), int(parts[1])))

    # a trivial greedy algorithm for filling the knapsack
    # it takes items in-order until the knapsack is full
    value = 0
    weight = 0
    taken = [0]*len(items)

    score=np.zeros((item_count+1,1+capacity))
    for i in range(1,item_count+1):
        for j in range(1,capacity+1):
            if(items[i-1].weight<=j):
                score[i][j]=max(score[i-1][j-items[i-1].weight]+items[i-1].value,score[i-1][j])
            else:
                score[i][j]=score[i-1][j]

    value=int(score[item_count][capacity])
    # print(score)
    val=capacity
    # print(item_count)
    for i in range(item_count-1,0,-1):
        # print(score[i+1][val],score[i][val])
        if score[i+1][val]!=score[i][val]:
            taken[i]=1
            val=val-items[i].weight

    # prepare the solution in the specified output format
    output_data = str(value) + ' ' + str(0) + '\n'
    output_data += ' '.join(map(str, taken))
    return output_data


if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')

