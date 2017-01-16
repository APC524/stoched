#!/bin/bash
# Parallel job using 4 processors:
#SBATCH -N 1
#SBATCH --ntasks-per-node=4
#SBATCH -t 0:03:00
#SBATCH --mail-type=begin
#SBATCH --mail-type=end
#SBATCH --mail-type=fail
#SBATCH --mail-user=kevinpg@princeton.edu
# Load openmpi environment
module load openmpi
# Make sure you are in the correct directory
cd ~/stoched/src/
# for nx in 128 256 512
# do
#    time ./heat_omp $nx 4 > heat_omp.$nx.4.out
#    gnuplot -e "outfile='heat_omp.$nx.4.out'" surf.plt
#    time srun ./heat_mpi $nx > heat_mpi.$nx.4.out
#    gnuplot -e "outfile='heat_mpi.$nx.4.out'" surf.plt
# done
time srun -n 4 ./stoched.exe example.parser.in init_file init_file.txt n_realizations 100000 suppress_print 1 > stoched_mpi.4.out