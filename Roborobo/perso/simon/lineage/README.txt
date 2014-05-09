simon.carrinon(at)lri.fr

2011 April
#!!!!
#!!!!
#NOT UP TO DATE
Here are some tools to study how genomes spread into the mEDEA robots population.


** 1. Drawing "phylorobotic" trees with :


They are two scripts taking a datalog file (FILENAME) in entry and returning a newick file (http://en.wikipedia.org/wiki/Newick_format) in the "./trees/" directory :  

	a- ./extractPrunedTree.sh BEGIN END FILENAME 
With this script you will be able to see where are come from genomes used by robots at the 'END'th generation.

	b- ./extractTree.sh BEGIN END FILENAME 
With this second you will be able to see all the "phylogenetic"/"phylogenetic" trees which grows during a mEDEA run.


!!WARNING as mEDEA explore a lot of place within the genome space search the trees might be really big, maybe too big to be handled with python (and you should modify the ./toNewick file to allow python to do more recursions)


	HOWTO have a look at thoses trees? see ./PHYLO.txt


** 2. Watch how evolves rate of common ancestors

./extractAncestorRate.sh BEGIN END DIRECTORY_NAME STEP

This script will parse all datalog_ file wrote by mEDEA in DIRECTORY_NAME and summarize them into a csv file which records : for all generation G between BEGIN and END the number of active robots at G and the number off unique ancestors they have in G-STEP . The .csv file will be stored in : ./ancestorsRawData/DIRECTORY_NAME.csv (with all other file need to build it)

./traceCommonAncestor.sh BEGIN END FILENAME

this script will print a graph allowing to watch the evolution of the "rate" of common ancestor between BEGIN and END. The graph will be wrote in : ./images/



BE CAREFUL :
	the number of robots used and the time of a generation need to be changed in ./to_Newick




TODO :
	Some things to do :
		- write a function that find the number of robot and the duration of a generation inside the right associated properties_ file
		- write a function which climbs back the tree to find the oldest common ancestor of a generation and plot it to watch how this value evolve (should be constant if just one common ancestor , grow up linearly if more?helpfull to look at speciation?)
		-ADD DEFAULT BEHAVIOR AND -h OPTIONS : where it prints how to use the script
