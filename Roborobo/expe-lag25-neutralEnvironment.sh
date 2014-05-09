#!/bin/sh

perl -pi -e 's/energyPointRespawnLagMaxValue.*/energyPointRespawnLagMaxValue = 25/' config/MedeaAggregation.properties
#perl -pi -e 's/margin.*/margin = 500/' config/MedeaAggregation.properties
./runParallal.sh -p "postExperimentMove.sh /home/jeanmarc/results/140116-NeutralEnvironment-Lag25-400K/" 200 config/MedeaAggregation.properties 7 > log25-neutralEnvironment
