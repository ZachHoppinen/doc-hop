#!/bin/bash
#SBATCH --job-name omp-mandelbrot #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 16 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:10:00 # run time. 10 minutes


if [ ! -e "./logs" ]; then
    mkdir logs
fi

echo "Loading Modules..."
module load gcc
module load openmpi/gcc/64
echo "Compiling..."
mkdir -p ../bin
gcc -fopenmp ../src/omp-mandelbrot.c -o ../bin/omp-mandelbrot.out
echo "Running..."
mkdir -p ../etc
../bin/omp-mandelbrot.out ../etc/omp-mandelbrot-$SLURM_JOB_ID.ppm 5000 5000
echo "Finished."
