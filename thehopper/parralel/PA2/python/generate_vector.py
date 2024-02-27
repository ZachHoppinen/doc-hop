## if you have a python interpreter, you can generate matrices in the format for the project
import random

y = input("how many cols?: ")
out = input("what to name file?: ")
line = "" + y + "\n"
for i in range(int (y)):
    line = line + str(random.randint(0, 9)) + "\n"

outdir = "../tests/test_files/Vectors/" + out

with open(outdir, 'w') as f:
    f.write(line)