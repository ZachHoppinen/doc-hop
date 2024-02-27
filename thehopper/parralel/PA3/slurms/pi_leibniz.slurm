#!/bin/bash
#SBATCH --job-name pi_leibniz #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 28 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p shortq # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 24:00:00 # run time. 5 minutes here.

module load gcc
module load openmpi/gcc/64/1.10.7

export OMPI_MCA_mca_base_component_show_load_errors=0

#Give serial first
g++ ../etc/pi_leibniz.cpp -o ../etc/leibiz_pi.out
echo "---------Serial---------------"
echo "Running 10000"
../etc/leibiz_pi.out 10000
echo "Running 1000000"
../etc/leibiz_pi.out 1000000
# echo "Running 20000000000"
# ../etc/leibiz_pi.out 20000000000

echo "4 processors"

echo "Running 10000"
mpirun -np 4 ../build/bin/pi_leibniz 10000
echo "Running 1000000"
mpirun -np 4 ../build/bin/pi_leibniz 1000000
echo "Running 20000000000"
mpirun -np 4 ../build/bin/pi_leibniz 20000000000

echo "8 processors"

echo "Running 10000"
mpirun -np 8 ../build/bin/pi_leibniz 10000
echo "Running 1000000"
mpirun -np 8 ../build/bin/pi_leibniz 1000000
echo "Running 20000000000"
mpirun -np 8 ../build/bin/pi_leibniz 20000000000

echo "16 processors"

echo "Running 10000"
mpirun -np 16 ../build/bin/pi_leibniz 10000
echo "Running 1000000"
mpirun -np 16 ../build/bin/pi_leibniz 1000000
echo "Running 20000000000"
mpirun -np 16 ../build/bin/pi_leibniz 20000000000

echo "20 processors"

echo "Running 10000"
mpirun -np 20 ../build/bin/pi_leibniz 10000
echo "Running 1000000"
mpirun -np 20 ../build/bin/pi_leibniz 1000000
echo "Running 20000000000"
mpirun -np 20 ../build/bin/pi_leibniz 20000000000

echo "25 processors"

echo "Running 10000"
mpirun -np 25 ../build/bin/pi_leibniz 10000
echo "Running 1000000"
mpirun -np 25 ../build/bin/pi_leibniz 1000000
echo "Running 20000000000"
mpirun -np 25 ../build/bin/pi_leibniz 20000000000
