#!/bin/sh
#######################################################################################33
#            runKongull.sh
#############################################
#
#     	This is a script for running RoboRobo witht the altruism
#	setup on Kongull
#
# These commands set up the environment for your job:
#
# Name of the job
#PBS -N RoboAltruism
#
# Account to run job (change the account name: See Accounting above)
#PBS -A acc-idi
#
# max walltime (must not exceed que max walltime)
#PBS -l walltime=00:55:00
#
# Specify resources number of nodes:cores per node
#PBS -l nodes=1:ppn=12
 
# Specify queue to submit to: default, bigmem, express or default
#PBS -q default


SSH_OPTS=' -o StrictHostKeyChecking=no -o BatchMode=yes '

cat $PBS_NODEFILE > nodes
 awk '!seen[$0]++' nodes > nodes-s

for node in `cat nodes-s`
	do
	FILES="/home/andhag/Roborobo/logs/oldPopulation/newGenomes/*"
	for f in $FILES
		do
		echo $node
		ssh $SSH_OPTS andhag@$node "cd Roborobo ; ./runParallal.sh 1 $f 1" &
	done
done

while [ 1 ]
do
	sleep 1
done

./checkEnd.sh
