#!/bin/bash
#SBATCH --job-name pi_leibniz_serial #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 1 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.
module load gcc

../build/bin/pi_leibniz 10000
../build/bin/pi_leibniz 1000000
../build/bin/pi_leibniz 2000000000
