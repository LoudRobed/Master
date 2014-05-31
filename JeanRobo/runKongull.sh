#!/bin/sh
#######################################################################################33
#            myjobscript.sh
#############################################
#
#     This is an example script example.sh
#
# These commands set up the environment for your job:
#
# Name of the job
#PBS -N test
#
# Account to run job (change the account name: See Accounting above)
#PBS -A freecycle
#
# max walltime (must not exceed que max walltime)
#PBS -l walltime=02:30:00
#
# Specify resources number of nodes:cores per node
# c-PBS -l nodes=1:ppn=1
#PBS -l nodes=2:ppn=12
 
# Specify queue to submit to: default, bigmem, express or default
#PBS -q optimist
 
# Cd to work directory
#cd $PBS_O_WORKDIR
#bin/myprogram

#cd Roborobo
#./roborobo -l config/MedeaAggregation.properties

SSH_OPTS=' -o StrictHostKeyChecking=no -o BatchMode=yes '

cat $PBS_NODEFILE > nodes
 awk '!seen[$0]++' nodes > nodes-s

for node in `cat nodes-s`
do
	echo $node
	ssh $SSH_OPTS andhag@$node "cd Roborobo ; ./runParallal.sh 100 config/MedeaAggregation.properties 12" &
	#ssh $SSH_OPTS jeanmarm@$node  echo "pouf" &
done

while [ 1 ]
do
	sleep 1
done
