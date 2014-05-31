#!/bin/sh
#PBS -N myjob
#PBS -A freecycle
#PBS -l walltime=00:00:02
#PBS -l nodes=1:ppn=1
#PBS -q optimist

./helloworld/helloworld
