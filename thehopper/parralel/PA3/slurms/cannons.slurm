#!/bin/bash

#SBATCH -J cannons
#SBATCH -o logs/cannon.o%j
#SBATCH -n 4
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 01:00:00
module load slurm
module load gcc
module load openmpi/gcc-6/1.10.3

export OMPI_MCA_mca_base_component_show_load_errors=0
echo "Cannons' 240x240"
mpirun ../build/bin/cannon 240
echo "Cannons' 1600x1600"
mpirun ../build/bin/cannon 1600
echo "Cannons' 4800x4800"
mpirun ../build/bin/cannon 4800

# Give serial first
# g++ ../etc/mm.cpp -o ../etc/mm
# echo "---------Serial---------------"
# ../etc/mm 240
# ../etc/mm 1600
# ../etc/mm 4800

# echo "--------4 Processors----------"
# echo "Cannon's on 240x240:"
# mpirun -np 4 ../build/bin/cannon 240
# echo "Cannon's on 1600x1600"
# mpirun -np 4 ../build/bin/cannon 1600
# echo "Cannon's on 4800x4800:"
# mpirun -np 4 ../build/bin/cannon 4800
# echo "--------9 Processors----------"
# echo "Cannon's on 240x240:"
# mpirun -np 9 ../build/bin/cannon 240
# echo "Cannon's on 1600x1600"
# mpirun -np 9 ../build/bin/cannon 1600
# echo "Cannon's on 4800x4800:"
# mpirun -np 9 ../build/bin/cannon 4800
# echo "--------16 Processors----------"
# echo "Cannon's on 240x240:"
# mpirun -np 16 ../build/bin/cannon 240
# echo "Cannon's on 1600x1600"
# mpirun -np 16 ../build/bin/cannon 1600
# echo "Cannon's on 4800x4800:"
# mpirun -np 16 ../build/bin/cannon 4800
# echo "--------25 Processors----------"
# echo "Cannon's on 240x240:"
# mpirun -np 25 ../build/bin/cannon 240
# echo "Cannon's on 1600x1600"
# mpirun -np 25 ../build/bin/cannon 1600
# echo "Cannon's on 4800x4800:"
# mpirun -np 25 ../build/bin/cannon 4800
