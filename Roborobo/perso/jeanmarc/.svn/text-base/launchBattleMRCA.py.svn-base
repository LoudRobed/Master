#!/usr/bin/python
# 2009 02 23 - niko(at)lri.fr
# 2009 07 20 - jeanmarc.montanier(at)lri.fr
# History:
#  Started from the basic log analyse script of nicolas bredeche
#
# Syntax :
#  To know it type 'sortBest -h'
#
# Hint :
#  All files with the ".dat" ending will be taken into account
#  Don't use the .dat extension for the output file

###
### import libraries
###

import glob
import os
import getopt
import re
import commands

import datetime
import sys
from random import choice

from array import array
from numpy import *  # history: numeric ... numarray ... numpy
from optparse import OptionParser
from shutil import *

import gc

def doubleCleaning (vectorToClean):
	cleanVector = []
	for i in vectorToClean:
		if cleanVector.count(i) == 0:
			cleanVector.append(i)
	return cleanVector

#function used to remove non-alpha-numeric characters
def clean(string):
	cleanedString = ""
	for i in string :
		if i.isalnum() or i == '.':
			cleanedString = cleanedString + i
	return cleanedString

# takes a float, tells if integer cast value is same value
def isInteger(value=0.0):
    if value == float(int(value)):
        return True
    else:
        return False

def computeQuartiles(thing={},avg=0.0,stddev=0.0):
	# prepare list
	values=[]
	if ( type(thing) == dict ):
		for item in thing:
			values.append(thing[item])
	else:
		values = thing

	if (len(values) == 0):
		values.append(0)
	values.sort()
	
	# compute stats
	medianIndex = (len(values) - 1.) / 2.
	lowerQuartileIndex = medianIndex / 2.
	upperQuartileIndex = medianIndex / 2. * 3.
	min    = values[0]
	max    = values[-1]
	
	if isInteger(medianIndex) is True:
		medianValue = values[int(medianIndex)]
	else:
		medianValue = ( values[int(medianIndex)] + values[int(medianIndex)+1] ) / 2.
	
	if isInteger(lowerQuartileIndex) is True:
		lowerQuartileValue = values[int(lowerQuartileIndex)]
	else:
		lowerQuartileValue = ( values[int(lowerQuartileIndex)] + values[int(lowerQuartileIndex)+1] ) / 2.
	
	if isInteger(upperQuartileIndex) is True:
		upperQuartileValue = values[int(upperQuartileIndex)]
	else:
		upperQuartileValue = ( values[int(upperQuartileIndex)] + values[int(upperQuartileIndex)+1] ) / 2.
	
	# display stats (whisker+box values)
	return [min,lowerQuartileValue,medianValue,upperQuartileValue,max]

def getMRCA(strains,iteration,length):
	localStrains = []
	beginIteration = iteration
	currentIteration = iteration 

	while (currentIteration > (beginIteration - 2*length)) or ((len(localStrains) != 1) and (currentIteration > 0)):
		if strains.has_key(str(currentIteration)):
			strainsOfThisIteration = {}
			for dest in strains[str(currentIteration)].keys():
				strainsOfThisIteration[dest] = strains[str(currentIteration)][dest]
				if (localStrains.count(dest) == 0) and (int(dest/1000) > (beginIteration - 2*length)) :
					localStrains.append(strains[str(currentIteration)][dest])
				else :
					for id,val in enumerate(localStrains):
						if val == dest:
							localStrains[id] = (strains[str(currentIteration)][dest])
			for dest in strainsOfThisIteration.keys():
				if localStrains.count(dest) != 0:
					for id,val in enumerate(localStrains):
						if val == dest:
							localStrains[id] = strainsOfThisIteration[dest]
			localStrains = doubleCleaning(localStrains)
		currentIteration -= 1

	return localStrains[0]

def getLineage(strains,root):
	currentRoot = root
	currentIteration = root/1000

	lineage=[]
	newRootFound = True
	while (newRootFound == True):
		newRootFound = False
		while (currentIteration > 0):
			if strains.has_key(str(currentIteration)):
				if strains[str(currentIteration)].has_key(currentRoot):
					lineage.append(currentRoot)
					currentRoot = strains[str(currentIteration)][currentRoot]
					newRootFound = True
					break
			currentIteration -=1
	
	return lineage
		

usage = "usage %prog [options]"
parser = OptionParser()
parser.add_option("-d","--directory",dest="dataDirectory",help="Search the .log file in DIRECTORY (default value = current directory). The script will recursively search with a depth of 2", metavar="DIRECTORY", default=".")
parser.add_option("-f","--file",dest="logFile",help="The log file that has to bee analyzed by the script (default value = none)", default="none")
parser.add_option("-b","--begin",dest="begin",help="Start to plot the curve from the FIRST evaluation (default value = 0)", metavar="FIRST", default="0")
parser.add_option("-e","--end",dest="end",help="Stop to plot the curve at the LAST iteration (default value = 0). If the value 0 it will stop at the last iteration of the log", metavar="LAST", default="0")
parser.add_option("-s","--step",dest="step",help="take individual randomely every STEP generation for the battle (default value = 10)", metavar="STEP", default="10")

parser.add_option("-l","--lifeTime",dest="lifeTime",help="life time of the robots in the considered experiments (default = 400)", metavar="LIFETIME", default="400")
parser.add_option("-n","--battleNumber",dest="battleNumber",help="NUMBER of battle that will be done on one file (default 1)", metavar="NUMBER", default="1")
parser.add_option("-o","--outputFile",dest="outputFile",help="The resulting eps file will be stored at OUTPUTFILE.eps, and the resulting log file will be store at OUTPUTFILE.log (default value = res)", metavar = "OUTPUTFILE", default="res")
parser.add_option("-r","--run", action = "store_true", dest="run",help="Should be true in order to run the battle. If false, use directly the OUTPUTFILE.log (default False). If false you have to provide the option --nbFiles.", default=False )
parser.add_option("-t","--lengthBattle",dest="lengthBattle",help="length of each battle in number of iteration (default 1000).", metavar="LENGTHBATTLE", default="1000")
(options, args) = parser.parse_args()

if (not options.logFile == "none"):
	if os.path.isfile(options.logFile):
		filenames=[options.logFile]
	else:
		parser.error("The path ("+ str(options.logFile) + ") doesn't lead to any file")

else:
	# search for all files in current directory with ".log" extension
	path=options.dataDirectory + '/'
	filenames = glob.glob(os.path.join(path,'datalog_*.txt'))
	temp = glob.glob(os.path.join(path,'*/datalog_*.txt'))
	if len(temp) > 0:
		for name in temp:
			filenames.append(name)

# display general information

print '#'
print '# Sort the X best individuals from the logs of the Cortex board.'
print '# ' + str(datetime.datetime.now().ctime())
print '#'
print '# source(s):'
for filename in filenames:
    print '#\t' + filename + '\n',
print '#'
print '#'


# "define" data index in matches of the patterns
idEvEvaluation = 1
idEvRobot = 2
idEvEnergy = 3
idEvDeltaEnergy = 4
idEvGenomeListSize = 5
idGendefEvaluation = 1
idGendefRobot = 2

allGenerations=[]

if (options.run == True ):
	if os.path.exists("./" + options.outputFile + ".log"):
		os.remove("./" + options.outputFile + ".log")

	for filename in filenames:
		print filename
		#	Initialization
		map={}
		strains = {}
		lowestIteration=0
		highestIteration=0

		filePath = os.path.dirname(filename)

		print "load log file : " + str(datetime.datetime.now().ctime())

		for line in open(filename,'r').readlines():
			patternDescription = "([0-9]+) : ([0-9]+) E (\-?[0-9]+\.?[0-9]*) DE (\-?[0-9]+\.?[0-9]*) GenomeLS ([0-9]+)"
			patternEvaluation = re.compile(patternDescription)
			match = patternEvaluation.match(line)
			if(match):
				if(not map.has_key(match.group(idEvEvaluation))):
					map[match.group(idEvEvaluation)] = {}
				if(not map[match.group(idEvEvaluation)].has_key(match.group(idEvRobot))):
					map[match.group(idEvEvaluation)][match.group(idEvRobot)] = {}
				map[match.group(idEvEvaluation)][match.group(idEvRobot)]['deltaEnergy'] = int(float(match.group(idEvDeltaEnergy)))
				map[match.group(idEvEvaluation)][match.group(idEvRobot)]['genomeListSize'] = int(match.group(idEvGenomeListSize))

			patternDescription = "([0-9]+) : ([0-9]+) use (.*)"
			patternGenome = re.compile(patternDescription)
			generationEvaluation = re.compile("([0-9]+) \: ([0-9]+) (t|take) ([0-9]+).*")

			genomeMatch = patternGenome.match(line)
			if(genomeMatch):
				idIteration = genomeMatch.group(idGendefEvaluation)
				idBot = genomeMatch.group(idGendefRobot)
				genome = re.split(" ",genomeMatch.group(3))
				genome = genome[:-1]
				if(not map.has_key(str(int(idIteration)))):
					map[str(int(idIteration))] = {}
				if(not map[str(int(idIteration))].has_key(idBot)):
					map[str(int(idIteration))][idBot] = {}
				map[str(int(idIteration))][idBot]['genome'] = genome

			matchGeneration = generationEvaluation.match(line)
			if matchGeneration :
				if not strains.has_key(matchGeneration.group(1)):
					strains[matchGeneration.group(1)] = {}
				strains[matchGeneration.group(1)][(int(matchGeneration.group(1))*1000)+int(matchGeneration.group(2))] = int(matchGeneration.group(4))
				if lowestIteration == 0 and highestIteration == 0:
					lowestIteration = matchGeneration.group(1)
					highestIteration = matchGeneration.group(1)
				elif int(matchGeneration.group(1)) > int(highestIteration) :
					highestIteration = matchGeneration.group(1)
				elif int(matchGeneration.group(1)) < int(lowestIteration) :
					lowestIteration = matchGeneration.group(1)

		resultList = {}
		generations=[]
		selectedRobotList = {}
		selectedCpt = 0

		copyfile('battleheadAggregation','./config/MedeaAggregationBattle.properties')
		battleFile = open('./config/MedeaAggregationBattle.properties',"a")
		battleFile.write('gMaxIt=  ' + options.lengthBattle + '\n' )
		inTheBattle = ""

		print "look for genomes to place in battle"

		mrca = getMRCA(strains,int(highestIteration),int(options.lifeTime))
		linage = getLineage(strains,mrca)
		if len(linage) == 0:
			print "That file was bad, next file"
			continue
		linageBegin = linage[-1]/1000
		linageEnd = linage[0]/1000

		maxIteration = 0
		if options.end == '0':
			maxIteration = linageEnd
		else:
			maxIteration = int(options.end)
		
		strains.clear()
		gc.collect()

		for iterationPass in range(int(linageBegin),maxIteration,int(options.step)*int(options.lifeTime)):
			iteration = iterationPass

			#look for the closest genome after that iteration
			choiceList = []

			while (len(choiceList) == 0):
				iteration +=1
				for root in linage:
					if (root/1000 == iteration ):
						choiceList.append((root-(root/1000)*1000))

			inTheBattle += str(iteration) + " " 
			
			selectedRobot = choice(choiceList)
						
			selectedRobotList[selectedCpt] = {}
			selectedRobotList[selectedCpt]['genome'] = map[str(iteration)][str(selectedRobot)]['genome']
			selectedRobotList[selectedCpt]['deltaEnergy'] = map[str(iteration)][str(selectedRobot)]['deltaEnergy']
			selectedRobotList[selectedCpt]['genomeListSize'] = map[str(iteration)][str(selectedRobot)]['genomeListSize']
			selectedRobotList[selectedCpt]['generation'] = iteration
			generations.append(iteration)
			allGenerations.append(iteration)

			geneCpt = 0
			for gene in map[str(iteration)][str(selectedRobot)]['genome']:
				battleFile.write('genomeToLoad'+str(selectedCpt)+'['+str(geneCpt)+'] = '+gene+'\n')
				geneCpt +=1

			selectedCpt +=1

		battleFile.write('nbGenomeToLoad=  ' + str(selectedCpt) + '\n' )
		battleFile.close()
		print inTheBattle

		map.clear()
		gc.collect()

		for battleId in range(int(options.battleNumber)):

			print "launchBattle -- " + filename + " --(" +str(battleId) + "/" + options.battleNumber  + ") : " + str(datetime.datetime.now().ctime())

			battleOutput = commands.getoutput("./roborobo -l config/MedeaAggregationBattle.properties")	
			print battleOutput

			print "load battle result : " + str(datetime.datetime.now().ctime())
			battleResult = open("logs/log.txt",'r').readlines()

			finalGenome={}
			genomeDescription = "([0-9]+) : ([0-9]+) use (.*)"
			patternGenome = re.compile(genomeDescription)
			patternDie = re.compile("([0-9]+) : ([0-9]+) die")
			for j in range(len(battleResult)):
					genomeMatch = patternGenome.match(battleResult[j])
					if(genomeMatch):
						idIteration = genomeMatch.group(idGendefEvaluation)
						idBot = genomeMatch.group(idGendefRobot)
						genome = re.split(" ",genomeMatch.group(3))
						genome = genome[:-1]
						if(not finalGenome.has_key(idBot)):
							finalGenome[idBot] = {}
						finalGenome[idBot] = genome

					dieMatch = patternDie.match(battleResult[j])
					if(dieMatch):
						idBot = dieMatch.group(idGendefRobot)
						if(finalGenome.has_key(idBot)):
							del finalGenome[idBot]

			genomePie={}
			for robot in selectedRobotList:
				genomePie[robot] = {}
				genomePie[robot]['genome'] = selectedRobotList[robot]['genome']
				genomePie[robot]['cpt'] = 0
				genomePie[robot]['deltaEnergy'] = selectedRobotList[robot]['deltaEnergy']
				genomePie[robot]['genomeListSize'] = selectedRobotList[robot]['genomeListSize']
				genomePie[robot]['generation'] = selectedRobotList[robot]['generation']

			for robot in finalGenome:
				for robotComp in genomePie:
					if ( finalGenome[robot] == genomePie[robotComp]['genome'] ):
						genomePie[robotComp]['cpt'] += 1

			resFile = open(options.outputFile + '.log',"a")
			for robot in genomePie:
				resFile.write( "----------------------"+'\n')
				resFile.write( filename +'\n')
				resFile.write( "cpt : " + str(genomePie[robot]['cpt']) +'\n')
				if len(finalGenome) > 0:
					resFile.write( "percentage : " + str(float(genomePie[robot]['cpt'])/float(len(finalGenome))) +'\n')
				else:
					resFile.write( "percentage : 0\n")
				resFile.write( "genome : " + str(genomePie[robot]['genome'])+'\n')
				resFile.write( "deltaEnergy : " + str(genomePie[robot]['deltaEnergy'])+'\n')
				resFile.write( "genomeListSize : " + str(genomePie[robot]['genomeListSize'])+'\n')
				resFile.write( "generation : " + str(genomePie[robot]['generation'])+'\n')

				if not resultList.has_key(genomePie[robot]['generation']):
					resultList[genomePie[robot]['generation']] = []

				resultList[genomePie[robot]['generation']].append(genomePie[robot]['cpt'])
			resFile.close()

			del genomePie

		print "print battle result of the file: " + str(datetime.datetime.now().ctime())

		#for generation in resultList:
		#	for toComplete in range (int(options.battleNumber) - len(resultList[generation])):
		#		resultList[generation].append(0)
		
		#for generation in completeResultList:
		#	for toComplete in range (int(options.battleNumber) - len(completeResultList[generation])):
		#		completeResultList[generation].append(0)

		fileData = open("tmp.dat","w")
		#for key in resultList :
			#quartile = computeQuartiles(resultList[key])
			#fileData.write(str(key) + "," + str(quartile[0]) + "," + str(quartile[1]) + "," + str(quartile[2]) + "," + str (quartile[3]) + "," + str(quartile[4])+ '\n')

		for generation in generations:
			generationToCheck = generation 
			if resultList.has_key(generationToCheck):
				fileData.write(str(generationToCheck) + "," + str(sum(resultList[generationToCheck])/len(resultList[generationToCheck])) + "\n")
			else:
				fileData.write(str(generationToCheck) + ",0\n")
		fileData.close()

		cpt = 2
		#logPlotContent='plot \'tmp.dat\' using 1:' + str(cpt+1) + ':'+ str(cpt) + ':' + str(cpt+4) + ':' + str(cpt+3) +' with candlesticks lt 3 lw 2 title \'Distibution the battles winner among generations\' whiskerbars, \'\' using 1:' + str(cpt+2) + ':'+ str(cpt+2) + ':' + str(cpt+2) +':' + str(cpt+2) + ' with candlesticks lt -1 lw 2 notitle,'
		logPlotContent = 'plot \'tmp.dat\' using 2:xtic(1) ti col ,'
		logPlotContent = logPlotContent[:-1]

		copyfile('logplotheadBa',filePath + '/logplot.gp')
		fileGnuplot = open(filePath + '/logplot.gp',"a")
		fileGnuplot.write('set output \'' + re.sub('\.txt','Battle.eps',filename) + '\'\n')
		fileGnuplot.write(logPlotContent)
		fileGnuplot.close()

		gnuPlotOutput = commands.getoutput("gnuplot " + filePath + "/logplot.gp")	
		print gnuPlotOutput
		del resultList
		del map
		del selectedRobotList

completeResultList = {}

if (len (allGenerations) > 0):
	for generation in allGenerations:
		completeResultList[generation] = []

resFile = open(options.outputFile + '.log',"r")
resContentArray = resFile.readlines()

highestGeneration = 0

for j in range(len(resContentArray)):
	patternDescription = "----------------------"
	patternEvaluation = re.compile(patternDescription)
	match = patternEvaluation.match(resContentArray[j])
	if (match):
		generation = 0
		percentage = 0

		generationDescription = "generation : ([0-9]+)"
		generationEvaluation = re.compile(generationDescription)
		generationMatch = generationEvaluation.match(resContentArray[j+7])
		if (generationMatch):
			generation = int(generationMatch.group(1))
			if generation > highestGeneration:
				highestGeneration = generation
		else:
			print "Error : There is no generation value in the line " + str(j+7) + " : " + resContentArray[j+7]
			exit()

		percentageDescription = "percentage : ([0-9]+\.?[0-9]*)"
		percentageEvaluation = re.compile(percentageDescription)
		percentageMatch = percentageEvaluation.match(resContentArray[j+3])
		if (percentageMatch):
			percentage = percentageMatch.group(1)	
		else:
			print "Error : There is no percentage value in the line " + str(j+3) + " : " + resContentArray[j+3]
			exit()

		if (completeResultList.has_key(generation)):
			completeResultList[generation].append(float(percentage))
		else:
			completeResultList[generation]=[float(percentage)]

resFile.close()

print "print complete battle result : " + str(datetime.datetime.now().ctime())

if (not len(allGenerations) > 0):
	allGenerations=sorted(completeResultList)


#gropu all results
generationDisp =[]
step = 0
if (not int(options.end) == 0):
	step = int(int(options.end)/20)
	generationDisp = range(step/2,int(options.end)-(step/2)+1,step)
else:
	step = int((float(highestGeneration)/20.0)+1.0)
	generationDisp = range(step/2,highestGeneration,step)


toDisplay = {}
for currentGeneration in completeResultList:
	found=False
	for generation in generationDisp:
		if abs(currentGeneration-generation) <= float(step/2.0):
			found=True
			if not toDisplay.has_key(generation):
				toDisplay[generation]= completeResultList[currentGeneration]
			else:
				toDisplay[generation] += completeResultList[currentGeneration]
			break
	if found==False:
		print currentGeneration
		print generationDisp
		print step
		print "not found to whom it should be matched"
		exit()

fileData = open("tmp.dat","w")
for generation in generationDisp:
	#fileData.write(str(generation) + "," + str((float(len(toDisplay[generation]))/((float(options.battleNumber))*nbOfFileUsed))*100) + "\n")
	#fileData.write(str(generation) + "," + str(float(len(toDisplay[generation]))) + "\n")
	if toDisplay.has_key(generation):
		fileData.write(str(generation) + "," + str((sum(toDisplay[generation])/float(len(toDisplay[generation])))*100.0) + "\n")
	else:
		fileData.write(str(generation) + ", 0\n")
fileData.close()

cpt = 2
#logPlotContent='plot \'tmp.dat\' using 1:' + str(cpt+1) + ':'+ str(cpt) + ':' + str(cpt+4) + ':' + str(cpt+3) +' with candlesticks lt 3 lw 2 title \'Distibution the battles winner among generations\' whiskerbars, \'\' using 1:' + str(cpt+2) + ':'+ str(cpt+2) + ':' + str(cpt+2) +':' + str(cpt+2) + ' with candlesticks lt -1 lw 2 notitle,'
logPlotContent = 'plot \'tmp.dat\' using 2:xtic(1) ti col'
#title \'Average percentage of presence after a battle\','
#logPlotContent = logPlotContent[:-1]

copyfile('logplotheadBa','./logplot.gp')
fileGnuplot = open('./logplot.gp',"a")
fileGnuplot.write('set output \'' + options.outputFile + '.eps\' \n')
fileGnuplot.write(logPlotContent)
fileGnuplot.close()

gnuPlotOutput = commands.getoutput("gnuplot " + "./logplot.gp")	
print gnuPlotOutput
