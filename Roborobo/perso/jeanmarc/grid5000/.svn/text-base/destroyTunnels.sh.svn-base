#!/bin/bash

password=$1
timeStamp=$2
hostname=`hostname`

./sshExecuteCommand.sh jmontanier access.grenoble.grid5000.fr $password "ssh -S ~/.ssh/blah-$hostname.ctl -O exit jmontani@pl-ssh3.lri.fr"
ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -S ~/.ssh/blah.ctl -O exit jmontanier@access.grenoble.grid5000.fr

rm communication$timeStamp
rm communicationInProgress

