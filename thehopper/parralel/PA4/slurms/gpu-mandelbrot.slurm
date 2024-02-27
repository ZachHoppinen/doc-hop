#!/bin/bash
#SBATCH --job-name gpu-mandelbrot #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 1 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroomgpu # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:10:00 # run time. 10 minutes
#SBATCH --gres=gpu:1

if [ ! -e "./logs" ]; then
    mkdir logs
fi

echo "Loading NVIDIA Module..."
module load nvidia_hpcsdk
echo "Compiling..."
mkdir -p ../bin
nvcc ../src/gpu-mandelbrot.cu -o ../bin/mandelbrot.out
echo "Running..."
mkdir -p ../etc
../bin/mandelbrot.out ../etc/gpu-mandelbrot-$SLURM_JOB_ID.ppm 10000 3000