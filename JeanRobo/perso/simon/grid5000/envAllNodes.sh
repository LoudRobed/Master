#!/bin/bash
#send a command to all node
if [ "$1" == "-h" ]
then
	echo 'envAllNodes.sh :it will send a command in all nodes via ssh' 
	echo "need to be started on the job (try oarsub -C \$JOBID)"
else
	if [ "$OAR_NODEFILE" == "" ] 
	then
		echo "need to be started on your grid5000's job (try oarsub -C \$JOBID)"
	else
		for node in ` cat $OAR_NODEFILE | uniq `; do
			ssh -f root@$node -C $1 > $OAR_JOB_ID"."$node"
		done
	fi
fi
