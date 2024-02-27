#!/bin/bash

#SBATCH -J pi_test
#SBATCH -o logs/pi_l.9.o%j
#SBATCH -n 20
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 00:02:00
module load slurm
module load gcc
module load openmpi/gcc-6/1.10.3

export OMPI_MCA_mca_base_component_show_load_errors=0

echo "Pi l is:"
mpic++ le.cpp -o le.out
mpirun le.out 10000