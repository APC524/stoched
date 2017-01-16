#!/bin/bash
# Parallel job using 4 processors:
#SBATCH -N 1
#SBATCH --ntasks-per-node=4
#SBATCH -t 0:10:00
#SBATCH --mail-type=begin
#SBATCH --mail-type=end
#SBATCH --mail-type=fail
#SBATCH --mail-user=kevinpg@princeton.edu
# Load openmpi environment
module load openmpi
# Make sure you are in the correct directory
cd ~/stoched/examples/

srun -n 4 ../src/stoched_parallel.exe chem.parser.in init_file init_chem.txt t_final 10000000 n_realizations 16 suppress_print 1 > stoched_mpi.4.out


