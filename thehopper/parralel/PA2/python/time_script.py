import shlex
import subprocess
import os
from os.path import join
import pathlib
import numpy as np
import pandas as pd
import pickle

bin_dir = '/home/zacharykeskinen/CS430-TeamE/PA2/build/bin'
pickle_dir = '/home/zacharykeskinen/CS430-TeamE/PA2/python'
max_threads = 28
runs_per_thread = 5

def execute(cmd):
    if type(cmd) != list:
        cmd = shlex.split(cmd)
    result = subprocess.run(cmd, capture_output= True)
    return result

def parse_time(txt, mode):
    if type(txt) != str:
        txt= str(txt)
    if mode == 'fib':
        times = txt.split(': ')[1].replace('\\n', '').replace("'","")
    elif mode == 'pi':
        times = txt.split(r'Time taken: ')[-1].replace('\\n', '').replace("'","")
    return times.split(' ')

print('starting')

res = pd.DataFrame(columns = ['fib', 'pi_leibniz', 'pi_mc'])
sizes = {'small':{'fib':15, 'pi_leibniz':10000,'pi_mc':10000},\
        'med':{'fib':25, 'pi_leibniz':50000,'pi_mc':50000},\
        'large':{'fib':30, 'pi_leibniz':100000,'pi_mc':100000}}

sizes = {'small':{'pi_leibniz':10000,'pi_mc':10000},\
        'med':{'pi_leibniz':100000,'pi_mc':100000},\
        'large':{ 'pi_leibniz':1000000,'pi_mc':1000000}}

for size, size_dic in sizes.items():
    print(size)
    for func_type in size_dic.keys():
        print(func_type)
        args = size_dic[func_type]
        bin_exec = join(bin_dir, func_type)
        for threads in range(1, max_threads+1):
            os.environ['OMP_NUM_THREADS'] = str(threads)
            values = []
            for _ in range(runs_per_thread):
                result = execute(f'{bin_exec} {args}')
                assert result.returncode == 0, f"Function Failed. Error: {result.stderr}"
                value, units = parse_time(result.stdout, mode = func_type.split('_')[0])
                values.append(value)
            res.loc[threads, func_type] = values
    print(res)
    with open(join(pickle_dir, f'report2-{size}-pi.pkl'), 'wb') as f:
        pickle.dump(res, f)

