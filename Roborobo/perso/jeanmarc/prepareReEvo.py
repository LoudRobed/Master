#!/usr/bin/python
# 2010 04 20 - jeanmarc.montanier(at)lri.fr
# 2011 04 03 - Re use the launchReplay script as a launchReEvo script : jeanmarc.montanier(at)lri.fr


import glob
import os
import getopt
import re
import commands

import datetime
import sys

from optparse import OptionParser
from shutil import *


usage = "usage %prog [options]"
parser = OptionParser()
parser.add_option("-F","--file",dest="logFile",help="The log file that has to bee analyzed by the script (default value = none)", default="none")
parser.add_option("-O","--outputFile",dest="outputFile",help="Where the config will be saved", default="none")
parser.add_option("-g","--generation",dest="generation",help="Define from which generation the population should be replayed (default value = 1)", metavar="GENERATION", default="1")
parser.add_option("-l","--lifeTime",dest="lifeTime",help="life time of the robots in the considered experiments (default = 400)", metavar="LIFETIME", default="400")
parser.add_option("-t","--lengthReplay",dest="lengthReplay",help="length of the replay in number of iteration (default 400000).", metavar="LENGTHREPLAY", default="400000")

(options, args) = parser.parse_args()

if (not options.logFile == "none"):
	if not os.path.isfile(options.logFile):
		parser.error("The path ("+ str(options.logFile) + ") doesn't lead to any file")
else:
	parser.error("No log file given. This script refuse to work in those conditions !!")

if (options.outputFile == "none"):
	parser.error("No output file given. This script refuse to work in those conditions !!")

print '#'
print '# Replay the behavior of the specifed robot'
print '# ' + str(datetime.datetime.now().ctime())
print '#'
print '# Source:'
print '# ' + options.logFile;
print '# Generation :'
print '# ' + str(options.generation)
print '# LifeTime :'
print '# ' + str(options.lifeTime)
print '# LengthReplay :'
print '# ' + str(options.lengthReplay)
print '# Output :'
print '# ' + options.outputFile
print '#'

fileContentArray = open(options.logFile,'r').readlines()
filePath = os.path.dirname(options.logFile)

genomesToReplay = []

for line in fileContentArray:
	patternDescription = "([0-9]+) : ([0-9]+) use (.*)"
	patternGenome = re.compile(patternDescription)
	genomeMatch = patternGenome.match(line)
	if(genomeMatch):
		idIteration = genomeMatch.group(1)
		idBot = genomeMatch.group(2)
		generation = (int(idIteration)+1) / int(options.lifeTime)
		if ( generation == int(options.generation) ):
			genome = re.split(" ",genomeMatch.group(3))
			genome = genome[:-1]
			genomesToReplay.append(genome)

# modif a faire cote roborobo : si on trouve pas le genome, alors le robot est en attente de genome

if ( genomesToReplay == [] ):
	print "No active robot at generation" + options.generation + "in file" + options.logFile
	exit(1)


copyfile('reEvoHead',options.outputFile)
replayFile = open(options.outputFile,"a")
replayFile.write('gMaxIt=  ' + options.lengthReplay + '\n' )

genomeCpt = 0
for genome in genomesToReplay:
	geneCpt = 0
	for gene in genome :
		replayFile.write('genomeToReplay['+str(genomeCpt)+'][' + str(geneCpt) + '] = '+gene+'\n')
		geneCpt += 1
	genomeCpt += 1

replayFile.close()
