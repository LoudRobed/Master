#!/bin/sh 

passFile=$1
portId=1023

function findFreePort()
{
	freePortNotFound=1
	while [ $freePortNotFound -gt 0 ]
	do
			portId=$((portId + 1))
			freePortNotFound=`netstat -a  | grep $portId | wc -l`
	done
	echo $portId
}

SSH_OPTS=' -o StrictHostKeyChecking=no -o BatchMode=yes '

if [ ! -x "startExperimentOneNode.sh" ] ; then
	echo "startExperimentOneNode.sh is missing"
	exit
fi

echo "use : "
echo $GOOD_NODES

cat $GOOD_NODES

for node in `cat $GOOD_NODES`
do
	echo $node
	findFreePort()
	echo $portId >> $passFile
	nohup $SSH_OPT -N -f -R $portId:$node:22 root@$node >foo.out 2>foo.err </dev/null
	ssh $SSH_OPT root@$node ./startExperimentOneNode.sh $passFile &
done

