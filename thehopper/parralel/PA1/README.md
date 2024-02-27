<h1>PA 1: Toy Problems for Parallel Computing</h1>
<h3>Names: Cameron Collinsworth, Rizbanul Hasan, Logan Hurd, and Zach Keskinen</h3>
<h3>Class: CS 430 Fall 2022</h3>

This project contains exectuables for a number of problems to evaluate serial vs 
parralel implementations of each problem. The problems include: Fibonnaci
series calculations, pi estimators, and matrix-matrix or matrix vector multipliers.

This is was the first programming assignment and involved creating the serial
implementation of each problem.

<h2>Quickstart</h2>

<h3>Build Instructions</h3>

To build all programs and tests in Onyx:

To easily build and test, simply give executable permissions to the included build and test sctips:


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

<h4>Leibniz's Series</h4>

From build directory use:

```
bin/pi_leibniz
```

or if you wish to specify how many terms to use the Leibniz series:

```
bin/pi_leibniz <number-terms>
```

replacing `<number-terms>` with an integer number of terms you wish to have in the
series.

<h4>Monte Carlo</h4>

From build directory use:

```
bin/pi_mc
```

or if you wish to specify how many terms to use the monte carlo estimation:
```
bin/pi_lpi_mceibniz <number-terms>
```
replacing `<number-terms>` with an integer number of random observations to use.

<h4>Matrix-Vector Multiply</h4>

From build directory use:

```
bin/matrix_mul <path to matrix 1> <path to matrix 2>
```

<h4>Matrix-Matrix Multiply</h4>

From build directory use:

```
bin/matrix_mul <path to matrix> <path to vector>
```

<h4>Fibonnaci Numbers</h4>

From build directory use:

```
bin/fib <number>
```
replacing `<number>` with an integer indicating which value in the sequence you'd like to request.

<h2>Testing</h2>

<h3>Test Instructions</h3>

To run our tests in Onyx, run `ctest` after completing build instructions.

To list all available tests run `ctest -N`. 

To run only a specific test run `ctest -R <testname>`. Replacing `<testname>` with
the name of the test(s) you would like to run.


<h3>Test Descriptions</h3>

<h4>Leibniz's Series</h4>

 - LeibnizTest
    - CorrectValues - ensure that estimations of pis for different number of terms
    return approximately the correct magnitude of estimation for pi. These absolute
    errors have been selected to pass almost every time but will fail very rarely
    due to random chance.
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

 - MonteCarloTest
    - CorrectValues - ensure that estimations of pis for different number of terms
    return approximately the correct magnitude of estimation for pi. These absolute
    errors have been selected to pass almost every time but will fail very rarely
    due to random chance.
    - InvalidArg - Ensure that function handles incorrect input arguments, especially
    negative number of terms to use in the series.

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

(describe contents and coverage of tests here)


<h2>Observations/Reflections</h2>

Camron Collinsworth: 

This project was fun, but a little stressful at times. It was good to get more experience 
in C++, however this was also a challenge because I knew next to nothing going into the project. 
If anything, this was a great lesson in refarctoring and code design. My code started off as a 
terrible mess of sphaghetti with no real structure, but ended up fairly modular and reusable . I hope that 
this is beneficial in the future when I am working on this codebase. 

Rizbanul Hasan: 

This was fun project to work on. This is my first time working with C++ so had some initial difficulties. All the
team members did great and were very cooperative. Also, working with cmake and makefiles were a good experience. 
Eagerly waiting for how the rest of the semesters go. 

Logan Hurd: 

This is the first time I've worked with C++, and it was a good experience for me. My Teammates
did a great job and cooperated pretty well. I'm curious about what the rest of the semester has
to offer. It was convenient to use cmake, I wasn't the one who set it up so I'll have to look into
its features and usage on my own if i want to use it in other projects. There weren't any big 
challenges for me in this project. Camron and Zach took on all of the hardest stuff (they did great).

Zach Keskinen: 

Fun to get to work with C++ and build systems which are both very new to me. Found
coding up the actual src code pretty easy but spent way way too much time on getting
cmake and gtest packages working succesfully. Also started with using just a makefile
but wasn't able to integrate gtest into all the different computers. So I switched
to Cmake to ensure gtest would be downloaded and work on Onyx and all our computers.

<h2>Manifest</h2>

 - include
    - fib.h
    - matrix.h
    - matrix_utilities.h
    - pi_funcs.h
    - pi_leibniz.h
    - pi_mc.h
 - src
    - fib.cpp
    - matrix_mul.cpp
    - matrix_vector_mul.cpp
    - pi_leibniz.cpp
    - pi_mc.cpp
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
 - makefile
 - README.md
 - buildProject.sh
 - test.sh