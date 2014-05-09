#!/bin/bash

if [ ! -e passFile ]
then
echo "town the gateaway :"
read -s town
echo $town > passFile
echo "password for the gateaway :"
read -s password
echo $password > passFile
echo "name for the local computer :"
read -s name
echo $name >> passFile
echo "login for the local computer :"
read -s login
echo $login >> passFile
echo "password for the local computer :"
read -s localPass
echo $localPass >> passFile
echo `whoami` >> passFile
fi

oarsub -p "cluster='genepi'" -t deploy -l nodes=1,walltime=2 "./katapult -o roborobo.env --copy-ssh-key --sleep -a \"startExperimentOneNode.sh passFile\" /home/jmontanier/startExperimentAllNode.sh passFile"
