#!/bin/bash

hostStamp=$1

while [ -e ~/.ssh/blah.ctl ]
do
    sleep 10
done

freePortNotFound=1
portId=1023
while [ $freePortNotFound -gt 0 ]
do
    portId=$((portId + 1))
    freePortNotFound=`netstat -a  | grep $portId | wc -l`
done
echo $portId

nohup ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -S ~/.ssh/blah-$hostStamp.ctl -N -f -L $portId:lri5-216:22 jmontani@pl-ssh3.lri.fr >foo.out 2>foo.err </dev/null
nbLineError=$(cat foo.err | wc -l)
if [ $nbLineError -gt 1 ]
then
    echo "tunnel not built"
    cat foo.err
else
    echo "tunnel successfully built"
fi
