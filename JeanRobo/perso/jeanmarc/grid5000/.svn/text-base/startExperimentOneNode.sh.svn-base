#!/bin/bash

passFile=$1

cd jeanmarc/Roborobo-KinTournament
perl -pi -e 's/gHighestBoundRespawn.*/gHighestBoundRespawn = 100/' config/MedeaAltruism.properties
name=$(cat /etc/hostname)
theDate=$(date)
proc=$(grep processor /proc/cpuinfo | wc -l)
echo "$name : run roborobo on $proc proccessor :  $theDate"
./runParallal.sh -p "postExperimentTransmit.sh $HOME/$passFile 0 Resultats/test" 26 config/MedeaAltruism.properties $proc
theDate=$(date)
echo "$name : end $theDate"

