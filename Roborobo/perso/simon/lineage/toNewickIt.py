#!/usr/bin/python
#2011 04 1 - simon.carrignon(at)lri.fr
#
# Use some extract filers in order to extract phylo info
#

import os
import re
import glob
import datetime
import re
import math
import sys
import csv
from optparse import OptionParser
from shutil import *

from sys import stdout
from cStringIO import StringIO
from dendropy import TaxonSet, Tree, TreeList, Taxon
sys.setrecursionlimit(1500)

#####################################################
#To Get information about somme at the generation X
#cat ../../../../Dev/Roborobo/logs/datalog_20110404-17h52m27s900334us.txt | grep "^39599 : 28 " | sed -e "s/ /,/g"



# Verify that the begin and end options are ok in compare to the informations obtained in the file
def checkOptions(options,fileContentArray):
	#if the given begin option is less than 0, we will take the first iteration mark available in the file
	if ( int(options.begin) < 0 ):
		timeStampDescription = "([0-9]+) \: "
		timeStampEvaluation = re.compile(timeStampDescription)
		lineToTry = -1
		match = None
		while ((not match) and (lineToTry < (len(fileContentArray)-1))):
			lineToTry += 1
			match = timeStampEvaluation.search(fileContentArray[lineToTry])
		if lineToTry == len(extractfileContentArray)-1 :
			raise BadBeginOption, "Unable to find a first line to analyze"
		options.begin = match.group(1)

	#if the given end option is less than 1, we will take the last iteration mark available in the file
	if ( int(options.end) < 1 ):
		timeStampDescription = "([0-9]+) \: "
		timeStampEvaluation = re.compile(timeStampDescription)
		lineToTry = len(fileContentArray)
		match = None
		while ((not match) and (lineToTry >= 0)):
			lineToTry -= 1
			match = timeStampEvaluation.search(fileContentArray[lineToTry])
		if lineToTry < 0 :
			raise BadEndOption, "Unable to find a last line to analyze"
		options.end = match.group(1)

	#if begin or end options are obviously wrong, raise exceptions
	if ( int(options.begin) < 0 ):
		raise BadBeginOption, "Unable to find a first timeStamp greater than 0"
	if ( int(options.end) < 1 ):
		raise BadEndOption, "Unable to find a last timeStamp greater than 1"
	if ( int(options.begin) > int(options.end) ):
		raise BadOptions, "Last timeStamp is lower than first timeStamp"




#if the data file is already there backup the previous version.
def manageBackUp(dataFileName):
	dataFileNameBackup = dataFileName
	version = -1
	#Search the first available version number
	while ( os.path.exists(dataFileNameBackup) ):
		version += 1
		dataFileNameBackup = dataFileName + str(version)
	if ( not version == -1 ):
		move(dataFileName,dataFileNameBackup)

	return open(filePath + "/" + options.outputFile ,"a" )

#initialize the first generation and return a list with all new starting roots
def initAllPhy(begin,nRobots):
	allPhy= []
	if( begin == 0 ):
		begstr=""
	else:	
		begstr=str(begin-1)

	for i in range(nRobots):
	  allPhy.append(Tree(stream=StringIO(begstr + str(i)+';'), schema="newick",rooted=True))
	  allPhy[i].reroot_at(allPhy[i].nodes()[0])
	  for node in allPhy[i].preorder_node_iter():
			    node.genome = ""
			    node.label = begstr+str(i)
			    allPhy[i].seed_node = node

	  allPhy[i].reindex_taxa()
	return allPhy

def euclidianDist(g1,g2):
    if( g1 == "" or g2 == ""):return 0
    firstGenome = re.split(" ",g1)
    secondGenome = re.split(" ",g2)
    distance = 0.0
    for i in range(len(firstGenome)):
	    if ( (not firstGenome[i] == '') and (not secondGenome[i] == '') ):
		    distance += pow(float(firstGenome[i])-float(secondGenome[i]),2)
    distance = math.sqrt(distance)
    return distance 


##Read the log file and store data in tree file
def print_ascii(allPhy):
    nodes_len=""
    tr=""
    for tree in allPhy :
	nodes_len+=" "+str(len(tree.nodes()))
# Largely inspired by the jean marc's extractor
	tr += "||||"+ tree.as_string("newick",internal_labels=True,write_rooting=False)
	#if(len(tree.nodes())>1) : tree.as_ascii_plot(show_internal_node_labels=True,plot_metric='depth')
    print tr
    print nodes_len
    
#add atree to the list listree of trees. If there is already a tree with the same root than atree delete the older tree to put atree in place
def addTree(atree,listree):
    toDelete=None
    for tree in listree :
	if atree.seed_node.label == tree.seed_node.label : 
	    toDelete=tree
    if toDelete is not None : listree.remove(toDelete)
    listree.append(atree)

def createTreeFile(logFilname,quick,nRobots,gTime,cutDeadLeaf):
    print "############################"
    print "## Parsing of the logFile ##"
    
    fileContentArray = open(options.logFile,'r').readlines()
    currentTimeStamp = -1 # Detection of changement in the timestamps
    precTimeStamp = -1 # Detection of changement in the timestamps

    removeDone = False
    beg= int(options.begin)	
    nGen = int(options.end)	
    step = int(options.step)

    if(quick):table=[[-1 for i in range(nRobots)] for i in range(nGen + 1)]
	
   
    allPhy = []
    newAllPhy=allPhy
    allPhy=initAllPhy(beg,nRobots)
    print "G", 
    for line in fileContentArray:
		# A line is valid only if it starts by an interation number
		#timeStampDescription = 'Info\(([0-9]+)\) : robot nb.([0-9]+) take the genome from the robot nb.([0-9]+)' 
		timeStampDescription = '([0-9]+) : ([0-9]+) take ([0-9]+)*'
		timeStampEvaluation = re.compile(timeStampDescription)
		match = timeStampEvaluation.search(line)
		if ( match ):
			#Mechanism to detect a changement in the timestamps ( There might be many lines with the same timeStamp)
			timeStamp = (int(match.group(1))+1)#/gTime
			if (timeStamp > int(options.end)):
				break
			if ( currentTimeStamp == -1):
				precTimeStamp = timeStamp
			else:
				precTimeStamp = currentTimeStamp
			currentTimeStamp = timeStamp
			newGeneration = not (precTimeStamp == currentTimeStamp)
			#We continue to parse the file while we have not reached the first generation wanted
			if (timeStamp >= beg) :
			    #if(timeStamp == beg and allPhy == []) : allPhy = initAllPhy(beg-1,nRobots)
			    if ( newGeneration ):
					print "-"+str(timeStamp),
  	                   	        stdout.flush()
#					allRoot=[]
#					allPhy=newAllPhy
#					newAllPhy = []
			    father = int(match.group(3))
			    son = int(match.group(2))
    ################## tree dendropy  creation
			    sonId = str(son)
			    fatherId = str(father)
			    print("fater:" + fatherId + " son " + sonId)
			    for tree in allPhy :
				    if(cutDeadLeaf):
				     	if(timeStamp % 4000 == 0):
					    leaves= tree.leaf_nodes()
					    for l in leaves:
						#print(" leeaaff -----"+l.label+" div100 "+ str(int(l.label)/100)+" ts :"+str(timeStamp))
					    	if ( (int(l.label)/1000 < (timeStamp-1000)) and l.parent_node != None ):
							#print("ola1--------------------------")
							p= l.parent_node
	                                                p.remove_child(l)
	                                                while(p.is_leaf() and p.parent_node != None ) :
	                                                    f= p.parent_node
	                                                    f.remove_child(p)
	                                                    p=f
				    
				    n = None
				    ancestor = None #ancestor at the level N-S
				    allNodes = tree.nodes()
				   #Why look all node and not leaves only? Not sure but the dendropy function which gives us all leaves is faster than looking for leaves manually. And if you choose to look leaves only, be sure to no forget that they change during a generation. 
				    for node in allNodes :
				#	print("ola1-------------")
					#print("label:" + node.label)
					if(node.label == fatherId) :
					    n=node
				    if(n is not None):
					#print("ola0-------------")
					son=n.new_child(label=sonId)
					edgLen= int(int(sonId)/100) -int(int(fatherId)/100)  
					son.edge_length =edgLen 
					
					sonI= son.label #.split(' ')[1] 
					#gene = son.label.split(' ')[0]
					if((int(timeStamp) > beg + int(step) -1) and quick ):#used to cut everythng no more useful
					    ancestor=son.parent_node
					    while( (int(getGen(son))-int(getGen(ancestor))) != int(step ) ):
						ancestor = ancestor.parent_node
					    ancestorId = ancestor.label.split(' ')[1]
						#Create a new tree using the ancestor as root
					    new_tree = Tree(tree)
					    mrca_node = new_tree.find_node_with_label(ancestor.label)
					    new_tree.seed_node=mrca_node
					    new_tree.seed_node.parent_node = None
					    addTree(new_tree,newAllPhy)
					    table[int(timeStamp)][int(sonI)]=ancestorId
				        else :
				            newAllPhy = allPhy
    print "#       Parsing done.      #"
    print "############################"

    if(quick):
        s=""
        allFather=0
        for i in table:
    	    for j in i :
    			s+=  str(j)+","
    
    	    allFather=list(set(i))
    	    try :
    		allFather.remove(-1)
    	    except ValueError:
		#if the script goes here it's because all genomes are transmitted
		None
    	    allAlive=list(i)
    	    allAlive = filter (lambda a: a != -1, allAlive)
    	    s+=str(len(allFather))+","+str(len(allAlive))    #The count of robots which have transmitted ther genome is bind at the end of the matrix
    	    s+="\n"
        
        csvFilname="./ancestorsRawData/"+baseName+".csv" 
        print "#\t write the csv file in "+csvFilname	
        out=open(csvFilname,"w" )	
        out.write(s)
        out.close()
        print "#\tdone"
        print "#------------------------#"

    return allPhy


#Given a nodre, return the generation of this node
#The node should have a label : "Gen Robot" 
def getGen(node):
    return int(node.label.split(' ')[0])


####Fonction which write into the file "treeFileName" all tree stored in "toWrite" with at least two nodes

def printAllTree(treeFileName,toWrite):
    out=open(treeFileName,"w" )
    for tree in toWrite:
		if(len(tree.nodes())>2):
			out.write(tree.as_string("newick",internal_labels=False,write_rooting=False))
    out.close()
    print "--------------------------------------------------------"
    print "All trees writed in "+treeFileName
    print "--------------------------------------------------------"

#------------------------------------------------------------------------------------------------------------------------------------------#
#------------------------------------------------------------------------------------------------------------------------------------------#
#------------------------------------------------------------------------------------------------------------------------------------------#
#------------------------------------------------------------------------------------------------------------------------------------------#
#------------------------------------------------------------------------------------------------------------------------------------------#

if __name__ == "__main__":
  
  	#setup the parser
	usage = "usage %prog [options]"
	parser = OptionParser()
	parser.add_option("-F","--file",dest="logFile",help="The log file that has to be anlalyzed by the script (default value = ./merge.dat)", metavar="LOGFILE", default="./merge.dat")
	parser.add_option("-B","--begin",dest="begin",help="Start to extract data from the FIRST timeStamp (default value = -1). If the value is -1 it will start at the first timeStamp ", metavar="FIRST", default="-1")
	parser.add_option("-E","--end",dest="end",help="Stop to extract data the LAST timeStamp (default value = 0). If the value is  it will stop at the last timeStamp of the log", metavar="LAST", default="0")
	parser.add_option("-S","--step", dest="step",help="Extract data every STEP in seconds (default value = 7)", metavar= "STEP", default="7" )
	parser.add_option("-O","--outputFile", dest="outputFile",help="Name of the file where extracted data will be recorded (default = extract.dat)", metavar= "OUTPUTFILE", default="extract.dat" )
	parser.add_option("-N","--newick", dest="newick",help="Option used to know if : 0 the tree is delete during the construction of a csv storing data about ancestors of the current generation\n\t1 all the tree is writed in newick format\n\tthe tree is writted but withoud leaf deadbefore the end of the run.", metavar= "NEWICK", default=0 )
	
	
	#read options from the parser
	(options, args) = parser.parse_args()

	if ( not os.path.exists(options.logFile) ):
		parser.error("The given file \"" + options.logFile + "\" doesn't exist")

	print '# Extract data wanted by the user from a log file.'
	print '# ' + str(datetime.datetime.now().ctime())
	print '# You should not forget that : \n#\t *the script is for 100 robots, \n#\t *the duration of a generation is hardcoded inside the script.'
	#Initialization
	
	#Check if the newick file associated already exists
	baseName=os.path.split(options.logFile)[1]
	baseName=baseName.split('.')[0]
	quick = False
	cutDeadLeaf = False
	nRobots = 100
	gTime = 400 
	print "----------------"


	if(int(options.newick) == 0) : quick = True 		#option used to now if a tree will be build to be printed : if we want a tree it means we don't want to print the big "lineage" 
	if(int(options.newick) == 2) : cutDeadLeaf = True
	allPhy=createTreeFile(options.logFile,quick,nRobots,gTime,cutDeadLeaf)
	if(not quick) :
		baseName += "G"+options.begin+"toG"+options.end
		if(cutDeadLeaf) : baseName += "_pruned"
		treeFileName='trees/'+baseName+'.tree'
		printAllTree(treeFileName,allPhy)	



		
		
	print '# ' + options.logFile

    
	
