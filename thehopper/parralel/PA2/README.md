<h1>PA 2: Some OpenMP</h1>
<h3>Names: Camron Collinsworth, Rizbanul Hasan, Logan Hurd, and Zach Keskinen</h3>
<h3>Class: CS 430 Fall 2022</h3>

This project contains exectuables for a number of problems to evaluate serial vs 
parralel implementations of each problem. The problems include: Fibonnaci
series calculations, pi estimators, and matrix-matrix or matrix vector multipliers.

This is programming assignment two and involved adding OpenMP implementation of
each problem to our pre-exisiting serial implementation. Each program will show 
a result and run time for the OpenMP implementation.

<h2>Quickstart</h2>

<h3>Build Instructions</h3>

To build all programs and tests in r2:

To easily build and test, simply give executable permissions to the included build and test scripts:


```
chmod +x buildProject.sh

chmod +x test.sh
```

Next, run the scripts to build and test:

```
./buildProject.sh

./test.sh
```

Manual build, test, and run instructions:


```
module load gcc, cmake

export CXX=/cm/local/apps/gcc/9.2.0/bin/g++

module load 

mkdir build

cd build

cmake ..

make
```

To build only individual programs after running `cmake ..` and ensuring you are in the build directory:

```
# Make monte carlo pi estimation program
make pi_mc
# Make Leibniz series pi estimation program
make pi_leibniz
# Make Fibonacci number generator
make fib
# Make matrix matrix multiplier
make matrix_matrix_mul
# Make matrix vector multiplier
make matrix_vector_mul
```


<h3>Run Instructions</h3>

In order to run the programs not on the head nodes of r2 you will need to `cd` to the
`PA2/slurms` directory and send the appropriate sbatch file to the slurm manager. The 
output will then be logged in the `logs/` directory inside the `slurms/` directory.

For all programs the default number of threads is set to 8. If you wish to change 
this number edit the slurm files changing the 8 in both `#SBATCH --ntasks-per-node 8` 
and  `export OMP_NUM_THREADS=8` to the number of threads you wish to run on. The 
maximum number of physical threads is 28 on r2.

If you want to test whether the OpenMP program was properly linked and functioning
run `sbatch openmp_test.slurm` in the `slurms/` directory to see a print out of hello world
from 28 threads in the logs under openmp_test-{jobid}.log.

<h4>Leibniz's Series</h4>

From slurms directory use:

```
sbatch pi_leibniz.slurm
```

This will run three cases: 10,000, 1,000,000, and 2,000,000,000 terms.
If you wish to edit the number of leibniz terms used to estimate pi then edit the
values following `../build/bin/pi_leibniz` in the slurm file.

The output will be in the logs directory called pi_leibniz_openmp-{jobid}.log.

<h4>Monte Carlo</h4>

From slurms directory use:

```
sbatch pi_mc.slurm
```

This will run three cases: 10,000, 1,000,000, and 2,000,000,000 terms.
If you wish to edit the number of leibniz terms used to estimate pi then edit the
values following `../build/bin/pi_leibniz` in the slurm file.

The output will be in the logs directory called pi_leibniz_openmp-{jobid}.log.

<h4>Matrix-Vector Multiply</h4>

From slurms directory use:

```
sbatch matrix_vect_mul.slurm
```

This will run three cases: 50, 500, and 1000. All of which are square matrices multiplied by a vector of corresponding dimensions.
The arguments for matrix and vector files that are evaluated can be edited by changing the contests of the slurm file.

The output will be in the logs directory called m_v_multiply-{jobid}.log.

<h4>Matrix-Matrix Multiply</h4>

From slurms directory use:

```
sbatch matrix_mul.slurm
```

This will run three cases: 50x50, 500x500, and 1000x1000. All of which are square matrices.
The arguments for matrix files that are evaluated can be edited by changing the contests of the slurm file.

The output will be in the logs directory called m_multiply-{jobid}.log.
<h4>Fibonnaci Numbers</h4>

From slurms directory use:

```
sbatch fib.slurm
```

This will run three cases: 10, 30, and 40 Fibonnaci numbers..
If you wish to edit the number of leibniz terms used to estimate pi then edit the
values following `../build/bin/fib` in the slurm file.

The output will be in the logs directory called fib_openmp-{jobid}.log.

<h2>Testing</h2>

<h3>Test Instructions</h3>

To run our tests in r2 you will need to load the cmake module.

`module load cmake`

Then run `ctest` after completing build instructions.

To list all available tests run `ctest -N`. 

To run only a specific test run `ctest -R <testname>`. Replacing `<testname>` with
the name of the test(s) you would like to run.


<h3>Test Descriptions</h3>

<h4>Leibniz's Series</h4>

 - LeibnizSerial
    - CorrectValues - ensure that serial estimations of pis for different number 
    of terms return approximately the correct magnitude of estimation for pi. 
    These absolute errors have been selected to pass almost every time but will 
    fail very rarely due to random chance.
    - InvalidArg - Ensure that function handles incorrect input arguments, especially
    negative number of terms to use in the series.
   
 - LeibnizParrelel
    - CorrectValues - ensure that parralel estimations of pis for different number 
    of terms return approximately the correct magnitude of estimation for pi. 
    These absolute errors have been selected to pass almost every time but will 
    fail very rarely due to random chance.
    - InvalidArg - Ensure that function handles incorrect input arguments, especially
    negative number of terms to use in the series.

 - PiFuncsTests
    - StringIsInt - Checks that providing integer strings as inputs to the pi functions 
    return True.
    - StringNotInt - Checks that providing non-numeric or decimal inputs to the 
    pi functions throws an exception.
    - SuccessfulArgParser - ensure that providing various forms of command line 
    arguments integer number of terms for correct inputs.
    - Exceptions - ensure that providing various forms of command line 
    arguments throws exceptions with incorrect inputs. 

<h4>Monte Carlo</h4>

 - MonteCarloSerial
    - CorrectValues - ensure that serial estimations of pis for different 
    number of terms return approximately the correct magnitude of estimation for 
    pi. These absolute errors have been selected to pass almost every time but 
    will fail very rarely due to random chance.
    - InvalidArg - Ensure that serial function handles incorrect input arguments, 
    especially negative number of terms to use in the series.
   
 - MonteCarloParralel
    - CorrectValues - ensure that parralel estimations of pis for different 
    number of terms return approximately the correct magnitude of estimation for 
    pi. These absolute errors have been selected to pass almost every time but 
    will fail very rarely due to random chance.
    - InvalidArg - Ensure that parralel function handles incorrect input arguments, 
    especially negative number of terms to use in the series.

<h4>Matrix-Vector Multiply</h4>

- MatrixVectorMultiplyTests </br>
    - Test Correct Result - Ensures that the program produces the correct result from multiplication. </br>
    - Test Incorrect Result - Ensures that the program does not falsley identify a result as correect. </br>

<h4>Matrix-Matrix Multiply</h4>

- MatrixMultiplyTests </br>
    - Test Correct Result - Ensures that the program produces the correct result from multiplication. </br>
    - Test Incorrect Result - Ensures that the program does not falsley identify a result as correect. </br>

<h4>Fibonnaci Numbers</h4>

- FibTest </br>
    - HandlesNegInput - Ensures that the program can handle negative input. In that case the output will be -1 for every negative number.</br>
    - HandlesZeroInput - Ensures that function handles when the input is zero. Output will be zero.</br>
    - HandlesPosInput - Ensures that function can return nth Fibonacci number.

<h2>Observations/Reflections</h2>

Camron Collinsworth: 

I would say that PA2 was a lot less "work" than PA1 in terms of coding, but it was a lot more trial and error as well as thought about the problem I was solving. The parallel solution for matrix multiply is a bit tricky because the overhead needed to run multiple threads can be so costly that it makes more sense to run the multiplication in serial unless you are dealing with very very large data sets... or maybe i'm just clueless and it would always be faster. I did quite a lot of reading online and it seems that everyone had a very simple solution for this problem and had promising results. Unfortunate, in my implementation, I was having far more trouble in getting favorable speeds in parallel.  



Rizbanul Hasan: Using openMP is fun as it reduces the overall work. For Fibonacci, I tried to work with large input to see how the overall time turns out. This assignment was fun to do. 



Logan Hurd: Using openMP is a pain when dealing with pointers. With value types 
it's super easy, but using pointers and arrays causes a bunch of errors. In the 
end I got it to work by putting the pointers and arrays in '#pragma omp critical's 
and separating as much of the math as I could so that could actually be parallelized.



Zach Keskinen: Implementing openMP for this project was very easy. For my two 
problems it seemed to involve mostly just adding the for pragma and the reduction
plus operator. Similarily to last time the cmake build system which was complex 
to set up but made it super easy to add openMP flags to every executable.

The build system, readme and setting up the slurm files however was pretty challenging to make
sure we were loading the correct modules and gcc versions, had the right number of threads in
all the locations and were changing all the readme sections correctly.


<h2>Manifest</h2>

 - include
    - fib.h
    - matrix.h
    - matrix_utilities.h
    - pi_funcs.h
    - pi_leibniz.h
    - pi_mc.h
    - utilities.h
 - src
    - fib.cpp
    - fib_driver.cpp
    - matrix_mul_driver.cpp
    - matrix_vector_mul_driver.cpp
    - pi_leibniz.cpp
    - pi_leibniz_driver.cpp
    - pi_mc.cpp
    - pi_mc_driver.cpp
    - utilities.cpp
 - tests
    - test_files
       - Matrices
          - 3x3_1_Solution
          - 3x3_2_Solution
          - 4X4_1_Solution
          - 4x4_2_Solution
          - 5x5_1_Solution
          - mm1_3x3
          - mm1_4x4
          - mm1_5x5
          - mm2_3x3
          - mm2_4x4
          - mm2_5x5
          - mm3_3x3
          - mm3_4x4
          - mm4_3x3
          - mm4_4x4
       - Vectors
          - 3_1_Solution
          - 3_2_Solution
          - 4_1_Solution
          - 4_1_Solution
          - 5_1_Solution
          - 5_2_Solution
          - v_3
          - v_4
          - v_5
    - MatrixMultiplyTests.cpp
    - MatrixVectorMultiplyTests.cpp
    - PiTests.cpp 
    - FibTest.cpp
 - CMakeLists.txt
 - README.md
 - buildProject.sh
 - test.sh
