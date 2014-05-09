#!/bin/bash


usage()
{
	echo "USAGE: ./runTipi.sh [OPTIONS] ROBOT_LIST ITERATION ORIGINAL_LOG_FILE CONFIG_FILE NB_OF_INSTANCE "
	echo ""
	echo "OPTIONS"
	echo "	-p, --postExperiemtScript=SCRIPT_AND_PARAMETERS"
	echo "		Use the SCRIPT_AND_PARAMETERS after an experiment has been completed"
}

oneRun()
{
	#init variables
	config=$1
	postExperimentScript=$2

	isSuccess=0
	timeStamp=`date +%H%M%S%N`	

	#launch experiment
	./roborobo -l $config >"temp$timeStamp" 2>/dev/null

	#transmit log file if necessary
	if [ "$postExperimentScript" = "" ]
	then
		rm "temp$timeStamp"
	else
		. $postExperimentScript
	fi
	echo $config done
}

if [ $# -lt 5 ]
then
	usage
else

	nbInst=""
	nbExp=""
	config=""
	postExperimentScript=""

	while [ "$1" != "" ]
	do
			case $1 in
					-p | --postExperimentScript )	shift
																				postExperimentScript=$1
																				;;
					-h | --help )           			usage
																				exit
																				;;
					*) break
			esac
			shift
	done

	robotList=$1
	iteration=$2
	originalLogFile=$3
	config=$4
	nbInst=$5

	completeCnt=0
	totCnt=0
	
	for robotId in $robotList
	do
		while [ `jobs | wc -l` -ge $nbInst ] # check the number of instance currently running
		do
			jobs >/dev/null
			sleep 5
		done
		
		#create a new config file
		newConfig=${config%\.properties}$robotId.properties
		cp $config $newConfig
		#copy in it the genome to replay
		extractedGenome=`./extractGenome.py -F $originalLogFile -I $iteration -R $robotId`
		if [ "$extractedGenome" != "" ]
		then
			elementCpt=0
			gene=""
			for element in $extractedGenome
			do
				if [ $elementCpt -lt 2 ]
				then
					gene=$gene" "$element
					elementCpt=$((elementCpt+1))
				else
					gene=$gene" "$element
					echo $gene >> $newConfig
					gene=""
					elementCpt=0
				fi
			done
			#launch the replay
			oneRun $newConfig "$postExperimentScript" &
		else
			rm $newConfig
		fi
	done
	while [ `jobs | wc -l` -gt 0 ] # check the number of instance currently running
	do
		jobs >/dev/null
		sleep 5
	done
fi

