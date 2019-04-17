#!/bin/bash

#PBS -N Hw

#PBS -q default

#PBS -l nodes=2:ppn=2

#PBS -j oe
      
#PBS -V

cd $PBS_O_WORKDIR/ 
    
mpirun -machinefile $PBS_NODEFILE -np 4 ./HW Graph5.csv


