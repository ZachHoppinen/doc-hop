<h1>PA 3: Some MPI</h1>
<h3>Names: Camron Collinsworth, Rizbanul Hasan, Logan Hurd, and Zach Keskinen</h3>
<h3>Class: CS 430 Fall 2022</h3>

This project contains exectuables for a number of problems to evaluate serial vs 
parralel implementations of each problem. The problem types include: 
pi estimators, and matrix-matrix or matrix vector multipliers.

This is programming assignment three and involved adding MPI implementation of
each problem to our pre-exisiting serial implementation. Each program will show 
a result and run time for the MPI implementation.

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
# Make cannon's matrix matrix multiplier
make cannon
# Make matrix matrix multiplier
make matrix_matrix_mul
# Make matrix vector multiplier
make matrix_vector_mul
```


<h3>Run Instructions</h3>

In order to run the programs not on the head nodes of r2 you will need to `cd` to the
`PA3/slurms` directory and send the appropriate sbatch file to the slurm manager. The 
output will then be logged in the `logs/` directory inside the `slurms/` directory.

For all programs the default number of processors is set to 4. If you wish to change 
this number edit the slurm files changing the 4 in `#SBATCH --ntasks-per-node 4` 
to the number of threads you wish to run on.

If you want to test whether the MPI program was properly linked and functioning
run `sbatch MPI_test.slurm` in the `slurms/` directory to see a print out of hello world
from 10 processors in the logs under mpi_test-{jobid}.log.

<h4>Leibniz's Series</h4>

From slurms directory use:

```
sbatch pi_leibniz.slurm
```

This will run three cases: 10,000, 1,000,000, and 200,000,000 terms.
If you wish to edit the number of leibniz terms used to estimate pi then edit the
values following `../build/bin/pi_leibniz` in the slurm file.

The output will be in the logs directory called pi_leibniz_openmp-{jobid}.log.

<h4>Monte Carlo</h4>

From slurms directory use:

```
sbatch pi_mc.slurm
```

This will run three cases: 10,000, 1,000,000, and 200,000,000 terms.
If you wish to edit the number of leibniz terms used to estimate pi then edit the
values following `../build/bin/pi_leibniz` in the slurm file.

The output will be in the logs directory called pi_leibniz_openmp-{jobid}.log.

<h4>Matrix-Vector Multiply</h4>

From slurms directory use:

```
sbatch mpi_matrix_vect_mul.slurm
```

This will run three cases: 50, 500, and 1000. All of which are square matrices multiplied by a vector of corresponding dimensions.
The arguments for matrix and vector files that are evaluated can be edited by changing the contests of the slurm file.

The output will be in the logs directory called mpi_m_v_multiply-{jobid}.log.

<h4>Matrix-Matrix Multiply</h4>

From slurms directory use:

```
sbatch mpi_mm.slurm
```

This will run three cases: 50x50, 500x500, and 1000x1000. All of which are square matrices.
The arguments for matrix files that are evaluated can be edited by changing the contests of the slurm file.

The output will be in the logs directory called m_multiply-{jobid}.log.
<h4>Cannon's Matrix-Matrix Multiply</h4>

From slurms directory use:

```
sbatch cannons.slurm
```

This will run three cases: 240x240, 1600x1600, and 4800x4800 matrix multiplications
of identity (a00 = 1, a01 =2 ...) matrixe being multiplied. The output is only 
plotted for matrices smaller than 30x30 so to see output change the matrix size 
in the slurm file to less than 30 terms.

If you wish to edit the number of matrix terms used to then edit the
values following `../build/bin/fib` in the slurm file.

The output will be in the logs directory called cannons-{jobid}.log.

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

<h4>Cannons Multiplication</h4>

-  </br>
    - Test Correct Results - Checks that correct values of identiy matrix multiplications are produced.</br>
    - Test Incorrect Inputs - Ensures that function handles when the input is zero. Output will be zero.</br>

<h2>Observations/Reflections</h2>

Camron Collinsworth: 

Getting MPI to work was more work than I had originally imagined. A big issue for me was trying to visualize the different nodes each performing the task. Debugging a program that uses MPI was also more difficult. Drawing pictures of my problem was extremely helpful in my design, it made visualizing the division of work between the different processors much easier. In the future, I would spend much more time becoming familiar with how MPI_Scatter and MPI_Gather work, as they were a large source of my frusteration.


Rizbanul Hasan:

Previous two assignments were pretty easy comparing to MPI. Understanding MPI took a lot of time. 
The reading and example helped a lot. Mostly used MPI_send/MPI_Recv and MPI_Reduce for Pi estimations.
MPI_Reduce made the program much shorter. Initially got some wrong output for both the PIs. The reason
was I wrongly distribited task among processors and fixed it later when tested with different processors.


Logan Hurd:

MPI was really rough. There were a lot of odd specifics to work around and as
far as I could tell no way to make it look pretty. For my program (MVM) I used 
two MPI Bcasts, a MPI_Scatter, a MPI_Scatterv, and a MPI_Gatherv. Somehow, 
every single one of those managed to give me an individual headache. In the end 
I was able to cut it down to a (relatively) succinct program that is somewhat 
readable. My biggest issues were fumbling around with pointers and mixing up the
arrays of numbers and where they went in my MPI calls.
Making the slurm script and adding it to CMake was quick and easy.

Zach Keskinen: 

Cannon's algorithm was pretty challenging and took a lot time. I took a first
stab that just used MPI_recv and MPI_send and did all the calculation for which
pieces to send out and it worked but took about 500 lines of code. So once that
basic idea was working I went back and made much better use of MPI_Gatherv, 
MPI_make_submatrices, and MPI_types and was able to make something faster and
much easier to code up. It was cool to see how much easier a complex task could
be if you used the mass messaging and MPI types. With the types I did struggle
knowing whether arrays were my MPI array type or an actual array and generally
had to just test at each step before I knew but presumably if you worked with MPI
enough it would be more obvious what format an array was at a particular step of
the code.

For the build system, CMake was again very easy to just add the Include_MPI() line
in the cmake script and have it do all the work of finding the right implementation
and adding the appropriate library linkings for all our exectuables.

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
    - cannons.cpp
    - cannons_driver.cpp
    - matrix_mul_driver.cpp
    - matrix_vector_mul_driver.cpp
    - mpi_mat_vector_mul_driver.cpp
    - mpi_mat_mul_driver.cpp
    - pi_leibniz.cpp
    - pi_leibniz_driver.cpp
    - pi_mc.cpp
    - pi_mc_driver.cpp
    - utilities.cpp
 - slurms
    - logs
    - cannons.slurm
    - matrix_mul.slurm
    - matrix_vect_mul.slurm
    - mpi_mm.slurm
    - mpi_test.slurm
    - pi_leibniz.slurm
    - pi_mc.slurm
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
