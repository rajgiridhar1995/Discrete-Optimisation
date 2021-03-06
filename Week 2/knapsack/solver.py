import os
from subprocess import Popen, PIPE

def solve_it(input_data):

    # Writes the inputData to a temporay file

    tmp_file_name = 'tmp.data'
    tmp_file = open(tmp_file_name, 'w')
    tmp_file.write(input_data)
    tmp_file.close()

    # Runs the command: java Solver -file=tmp.data
    tmp_file = open(tmp_file_name, 'r')
    process = Popen(['./main'], stdin=tmp_file, stdout=PIPE)
    (stdout, stderr) = process.communicate()
    # print stdout
    # removes the temporay file
    os.remove(tmp_file_name)
    with open('filename', 'r') as input_data_file:
        input_data = input_data_file.read()
    lines=input_data.split('\n')
    firstLine=lines[0].split()
    output=str("%d 0\n" % (int(firstLine[0]),))
    output+=(str(lines[1]))
    return output


import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        input_data_file = open(file_location, 'r')
        input_data = ''.join(input_data_file.readlines())
        input_data_file.close()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')
