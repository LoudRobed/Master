#!/usr/bin/python
# 2010 10 27 - jeanmarc.montanier(at)lri.fr
#
# Extract a gene from a log file
#
# Syntax :
#  To know it type './extractGenome.py -h'

###
### import libraries
###
import os
import glob
import re

from optparse import OptionParser


if __name__ == "__main__":

	# Create the option parser
	usage = "usage %prog [options]"
	parser = OptionParser()
	parser.add_option("-F","--file",dest="logFile",help="The log file from where a genome will be extracted (default value = none)", default="none")
	parser.add_option("-I","--iteration",dest="iteration",help="The iteration from where the genome will be extracted (default = -1)",default=-1)
	parser.add_option("-R","--robotId",dest="robotId",help="The id of the robot from which the genome should be extracted (default = -1)",default=-1)

	#Read the options
	(options, args) = parser.parse_args()

	fileContentArray = []
	if (not options.logFile == "none"):
		if os.path.isfile(options.logFile):
			fileContentArray = open(options.logFile,'r').readlines()
		else:
			parser.error("The path ("+ str(options.logFile) + ") doesn't lead to any file")
	else:
		parser.error("One should give a log file in order to extract a genome from it")

	if (options.iteration == -1):
		parser.error("You have to precise an iteration")

	if (options.robotId == -1):
		parser.error("You have to precise a robot id")

	lineEvalution = re.compile("([0-9]+) : ([0-9]+) use (.*)")
	for line in fileContentArray :
		match = lineEvalution.match(line)	
		if match:
			readIteration = match.group(1)
			readId = match.group(2)
			genomeString = match.group(3)

			if ((readIteration == options.iteration) and (readId == options.robotId)):
				genome = re.split(" ",genomeString)
				geneCpt = 0
				for gene in genome:
					if len(gene) > 0:
						print "genomeToReplay[" + str(geneCpt) + "] = "+ gene
					geneCpt += 1

				break


