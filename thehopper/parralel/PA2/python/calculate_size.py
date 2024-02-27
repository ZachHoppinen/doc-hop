## if you have a python interpreter, you can generate matrices in the format for the project
## I am very aware that this code is shit. I'm not being graded on it, so leave me alone!

l1Size = 32*1024
l2Size = 1024*1024
l3Size = 24*1024*1024 ## l3 is freaking huge

m1R = input("how many rows in matrix 1?: ")
m1C = input("how many cols in matrix 1?: ")
m2R = input("how many rows in matrix 2?: ")
m2C = input("how many cols in matrix 2?: ")

m3R = int (m1R)
m3C = int (m2C)

m1Size =((8 * int (m1R) * int (m1C)) + 8)
m2Size =((8 * int (m2R) * int (m2C)) + 8)
m3Size =((8 * int (m1R) * int (m2C)) + 8)

print("size of matrix 1: " + str (m1Size))
print("size of matrix 2: " + str (m2Size))
print("size of result matrix: " + str (m3Size))

total_size = m1Size + m2Size + m3Size

if(m1Size <= l1Size):
    print("m1 fits in l1")
if(m1Size <= l2Size):
    print("m1 fits in l2")
if (m1Size <= l3Size):
    print("m1 fits in l3")
if(m2Size <= l1Size):
    print("m2 fits in l1")
if(m2Size <= l2Size):
    print("m2 fits in l2")
if (m2Size <= l3Size):
    print("m2 fits in l3")
if(m3Size <= l1Size):
    print("result fits in l1")
if(m3Size <= l2Size):
    print("result fits in l2")
if (m3Size <= l3Size):
    print("result fits in l3")
if ((m1Size + m2Size +m2Size) <= l1Size):
    print("all matrices fit in l1")
if ((m1Size + m2Size +m2Size) <= l2Size):
    print("all matrices fit in l2")
if ((m1Size + m2Size +m2Size) <= l3Size):
    print("all matrices fit in l3")


