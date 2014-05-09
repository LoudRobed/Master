#!/bin/bash
# send experience in all reserved node
# usage : ./testDifferentRessourceCap.sh START END STEP
# All ressource capacities (if enough nodes are reserved) will be tested between 
# START and END with a step of STEP. 
# to test all repartitions with a setup with 100 agents the commande is :
# ./testDifferentRessourceCap.sh 50 105 1

if [ "$1" == "" ]
then
	echo 'For all ressource s repartition (ie the number n of robots allowed on one sun, 100 - n for the other sun) between START and END with a step of STEP, the script will test all sparsities for the repartation in a reserved node using ssh.'
	echo ' usage : ./testDifferentRessourceCap.sh START END STEP'
	echo ' All ressources repartition (if enough nodes are reserved) will be tested between '
	echo ' START and END with a step of STEP. '
	echo ' to test all repartitions with a setup with 100 agents the commande is :'
	echo ' ./testDifferentRessourceCap.sh 50 105 1'
	echo '--output--'
	echo '  WARNINGS : notice that a free parition is mounted inplace of the logs folder to ensure that enough space is available on the node. But this could be specific of some cluster!'
	echo ' Because a lot of run will be done, the logs folders will be bunzipped.'
	echo ' The output of each node is writted in $JOBID.${node}_${repartition_tested}'
	exit 0
fi
if [ "$OAR_NODEFILE" == "" ]
then
	echo "need to be started on your grid5000's job (try oarsub -C \$JOBID)"
	exit 0
fi

per=$1
end=$2
step=$3

nExp=200
ncore=8

sparsStart=5
sparsEnd=95
sparsStep=5

for node in ` cat $OAR_NODEFILE | uniq `; do
	echo "rep,"$per"  run on :" $node":"
	echo "rep,"$per"  run on :" $node >> $OAR_JOB_ID.logRuns
	ssh -f root@$node -C "  cd simon/Roborobo/ && 
				sed -i \"s/gNbAllowedRobotsBySun = [0-9][0-9]/gNbAllowedRobotsBySun = $per/g\" prj/mEDEA-sp/propertieFiles/sparsity.properties && 
				mount /dev/sda5 logs	&&
				perso/simon/sparsity/testAllSparsity.sh $nExp \`cat /proc/cpuinfo | grep proc | sort | uniq | wc -l\` $sparsStart $sparsEnd $sparsStep  &&
				echo \"Bzip logs\" &&
				tar cjf logs.tbz logs &&
				echo \"jobdone.\"
	"> $OAR_JOB_ID"."$node"_"$per
	per=$((per + step))
	if [ $per -eq $end ] 
	then
		per=$1
	fi
done
