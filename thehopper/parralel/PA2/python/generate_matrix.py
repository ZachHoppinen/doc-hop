## if you have a python interpreter, you can generate matrices in the format for the project
import random

x = input("how many rows?: ")
y = input("how many cols?: ")
out = input("what to name file?: ")
line = "" + x + " " + y + "\n"
for i in range(int (x)):
    for j in range(int (y)):
        line = line + str(random.randint(0, 9)) + " "
    line = line + "\n"

outdir = "../tests/test_files/Matrices/" + out

with open(outdir, 'w') as f:
    f.write(line)