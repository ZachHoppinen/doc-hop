#!/usr/bin/env python3

import random
import re
import string
import sys
from pathlib import Path

if len(sys.argv) == 1: length = 15
elif len(sys.argv) == 2: length = int(sys.argv[1])
else: raise ValueError

data_path = Path(__file__).parent.joinpath('data', 'the_sonnets_1609.txt')
if __name__ == '__main__':
    with open(data_path) as f:
        lns = f.read().replace('\n', '')
    sonnets = [l.strip(' ').replace('  ', ' ') for l in re.split(r'(\d+)', lns) if len(l) > 30]
    symbols = string.printable[62:89]
    numbers = string.printable[:10]
    uppers = string.printable[36:62]

    sonnet = random.choice(sonnets)
    new_pass = ''
    while len(new_pass) < length:
        word = random.choice(sonnet.split(' ')).replace(',', '')
        symbol = random.choice(symbols)
        number = random.choice(numbers)
        upper = random.choice(uppers)
        if len(word) < 3: continue
        section = f'{word}{symbol}{upper}{number}'
        new_pass = new_pass + section

    print(new_pass)
