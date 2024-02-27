#!/bin/bash

#SBATCH -J time_test
#SBATCH -o /home/zacharykeskinen/CS430-TeamE/PA2/logs/report2-test.o%j
#SBATCH -n 28
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 00:02:00
module load slurm
module load gcc
module load openmpi/gcc-6/1.10.3
export OMPI_MCA_mca_base_component_show_load_errors=0

eval "$(conda shell.bash hook)"
conda activate cs530

python /home/zacharykeskinen/CS430-TeamE/PA2/python/time_script.py