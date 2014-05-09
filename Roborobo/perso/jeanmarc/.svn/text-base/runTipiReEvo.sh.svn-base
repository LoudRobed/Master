#! /bin/bash


usage()
{
	echo "USAGE: ./runTipi.sh [OPTIONS] NB_OF_EXP ORIGINAL_DATALOG_FILE NB_OF_INSTANCE "
	echo ""
	echo "OPTIONS"
	echo "	-p, --postExperiemtScript=SCRIPT_AND_PARAMETERS"
	echo "		Use the SCRIPT_AND_PARAMETERS after an experiment has been completed"
}

oneRun()
{
	#init variables
	mainTimeStamp=$1
	postExperimentScript=$2

	isSuccess=0
	timeStamp=`date +%H%M%S%N`	

	#launch experiment
	./roborobo -l config/ReEvo$originalDatalogParameter.properties >"temp$timeStamp" 2>/dev/null

	#transmit log file if necessary
	if [ "$postExperimentScript" = "" ]
	then
		#wait until can update the results
		while [ -e "take$mainTimeStamp" ]
		do
			sleep 1
		done
		#update results
		touch "take$mainTimeStamp" 
		count=$(cat	"complete$mainTimeStamp")
		count=$((count+1))
		echo $count > "complete$mainTimeStamp"
		rm "take$mainTimeStamp" 
		rm "temp$timeStamp"
	else
		. $postExperimentScript
	fi
}

if [ $# -lt 3 ]
then
	usage
else

	nbInst=""
	nbExp=""
	originalConfig=""
	postExperimentScript=""

	while [ "$1" != "" ]; do
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

	nbExp=$1
	originalDatalog=$2
	nbInst=$3

	mainTimeStamp=`date +%H%M%S%N`	
	completeCnt=0
	totCnt=0
	originalDatalogParameter=${originalDatalog#*/datalog_}

	./prepareReEvo.py -F $originalDatalog -O ./config/ReEvo$originalDatalogParameter.properties -g 1000 -t 40000

	echo "0" > "complete$mainTimeStamp"

	while [ $completeCnt -lt $nbExp ]
	do
		while [ `jobs | wc -l` -ge $nbInst ] # check the number of instance currently running
		do
			jobs >/dev/null
			sleep 5
		done

		while [ -e "take$mainTimeStamp" ]
		do
			sleep 1
		done
		touch "take$mainTimeStamp" 
		completeCnt=$(cat "complete$mainTimeStamp")
		rm "take$mainTimeStamp" 

		echo =-=-=-=-=-=
		echo "Success rate : $completeCnt/$totCnt"
		echo =-=-=-=-=-=

		if [ $completeCnt -lt $nbExp ]
		then
			oneRun $mainTimeStamp "$postExperimentScript" &
			totCnt=$((totCnt+1))
		fi
	done
	echo =-=-=-=-=-=
	echo "Success rate : $completeCnt/$totCnt"
	echo =-=-=-=-=-=
	echo $config >> complete$mainTimeStamp
	killall -9 runTipi.sh ; killall -9 roborobo;
fi

