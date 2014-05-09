#!/bin/bash
#usefull to bring back all logs directory made in a bunch of node

if [ "$1" == "-h" ]
then
	echo 'bringBackAllLogs.sh :usefull to bring back all logs directory made in a bunch of node' 
	echo "need to be started on the job (try oarsub -C \$JOBID), after a used of a script like testDifferentsRessourceCap.sh"
	echo 'It will bring back all logs directory in your grid5000 user account using names stored in $JOBID.logRuns.'
else
	if [ "$OAR_NODEFILE" == "" ] 
	then
		echo "need to be started on your grid5000's job (try oarsub -C \$JOBID)"
	else
		for node in ` cat $OAR_NODEFILE | uniq `; do
			foldername=`cat $OAR_JOBID.logRuns | grep $node |uniq | awk '{print $1}' | sed "s/,/_/g"`
			scp -r root@$node:~/simon/Roborobo/logs/ $OAR_JOB_ID.$foldername;
		done
	fi
fi
