#!/bin/bash

float_scale=2

function float_eval()
{
    local stat=0
    local result=0.0
    if [[ $# -gt 0 ]]; then
        result=$(echo "scale=$float_scale; $*" | bc -q 2>/dev/null)
        stat=$?
        if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    fi
    echo $result
    return $stat
}

if [ -e $1 ]
then
	nodes=""

	filter=$(grep "granduc-\[.*\]" $1)
	for line in $filter
	do
		reFilter=$(echo $line | grep "granduc-\[.*\]" )
		if [[ $reFilter != "" ]]
		then
			reFilter=${reFilter#*[}
			reFilter=${reFilter%]*}
			echo $reFilter
			splited=$(echo $reFilter | tr "," "\n")
			for elem in $splited
			do 
				check=$(echo $elem | grep "-" )
				if [[ $check != "" ]]
				then
					beginEnd=($(echo $elem | tr "-" "\n"))
					seq=$(seq ${beginEnd[0]} ${beginEnd[1]})
					for p in $seq
					do
						nodes=$nodes" "$p
					done
				else
					nodes=$nodes" "$elem
				fi
			done
			break
		fi
	done


	sumExtinctions=0
	sumRuns=0
	for node in $nodes
	do
		sanityCheck=$(grep "granduc-"$node".* Done : .*(1)" $1 | wc -l)
		if [ $sanityCheck -lt "2" ]
		then
			logStatus=$(grep "granduc-"$node".* Done : " $1 | tail -n 1)
			echo $node" : "$logStatus
			extinctions=${logStatus#*(}
			extinctions=${extinctions%)*}
			nbRuns=${logStatus#* :}
			nbRuns=${nbRuns%/*}
			sumExtinctions=$((sumExtinctions + extinctions))
			sumRuns=$((sumRuns + nbRuns))
		else
			echo "Not taken into account : "$node
		fi
	done
	echo $sumExtinctions"/"$sumRuns" : "`float_eval "$sumExtinctions/$sumRuns"`



fi
