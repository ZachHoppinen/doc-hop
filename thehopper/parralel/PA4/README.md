<h1>PA 4: Mandelbrot!! Final Programming Assignment</h1>
<h3>Names: Camron Collinsworth, Rizbanul Hasan, Logan Hurd, and Zach Keskinen</h3>
<h3>Class: CS 430 Fall 2022</h3>

This project contains exectuables to calculate and plot solutions to the mandelbrot
set using either the NVIDIA GPU or OpenMP Threading. Each implementation will show
the run time and output a image into the etc/ directory that can be copied to a 
local computer to view.

<h2>Quickstart</h2>

<h3>Run Instructions</h3>

In order to run the programs not on the head nodes of r2 you will need to `cd` to the
`PA4/slurms` directory and send the appropriate sbatch file to the slurm manager. The 
output will then be logged in the `logs/` directory inside the `slurms/` directory.

<h4>OpenMP-Implementation of Mandelbrot</h4>

From slurms directory use:

```
sbatch omp_mandelbrot.slurm
```

This will calculate the mandelbrot set on the classroom queue.
The arguments can be changed in the slurm file and are [1] - the output file
name, [2] - the maximum iterations to test each point to, [3] - the resolution
of the image in both directions. The space is set between -2 to 1 in the x-dimension
and -1.5 to 1.5 in the y axis. One can optionally add extra parameters when running
the program to override these bounds. To do this the slurm script would need to be 
modified. Four new arguments should be added to the omp-mandelbrot.out call:
```
../bin/omp-mandelbrot.out ../etc/omp-mandelbrot-$SLURM_JOB_ID.ppm <max iterations> <resolution> <minX> <maxX> <minY> <maxY>
```

The output will be in the logs directory called omp-mandelbrot-{jobid}.log and 
the image will by default by omp-mandelbrot-{jobid}.ppm in the etc/ directory.

<h4>GPU-Implementation of Mandelbrot</h4>

From slurms directory use:

```
sbatch gpu-mandelbrot.slurm
```

This will calculate the mandelbrot set using the a 2d block implementation on the
GPU. The arguments can be changed in the slurm file and are [1] - the output file
name, [2] - the maximum iterations to test each point to, [3] - the resolution
of the image in both directions. The space is set between -2 to 1 in the x-dimension
and -1.5 to 1.5 in the y axis.

The output will be in the logs directory called gpu-mandelbrot-{jobid}.log and 
the image will by default by gpu-mandelbrot-{jobid}.ppm in the etc/ directory.

<h2>Mandelbrot Set Description</h2>

The mandelbrot set is a set of numbers in the complex plane defined by whether the
orbit of the values starting at $C$ are bounded (stay close to the origin and 
don't approach infinity). The definition of the set is:

$$
z_{n+1} = z_n^2 + C
$$
with: 
$$
$z_{0} = C$
$$

<h2>Observations/Reflections</h2>

Camron Collinsworth: 

Rizbanul Hasan:

Logan Hurd:

Zach Keskinen: 

<h2>Manifest</h2>

 - src
    - mandelbrot.cu
    - omp-mandelbrot.c
 - slurms
    - logs
    - gpu-mandelbrot.slurm
    - omp_mandelbrot.slurm
 - README.md
