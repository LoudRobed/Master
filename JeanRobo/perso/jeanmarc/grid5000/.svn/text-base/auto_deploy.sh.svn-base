#!/bin/sh
# written by David Margery for the 2006 Grid'5000 spring school
# feel free to copy and adapt
# updated by Cyril Constantin
# update by David Margery, 2008, to accept parameters
# modification by Jean-Marc Montanier : 2011

# Parameters

# set your public key here :
KEY_FILE=~/.ssh/id_rsa.pub

####

echo -n "Script running on:" 
hostname

#Get the eventual parameters
if [ $# -gt 0 ] ; then
  ENVIRONMENT="$1"	
else
  ENVIRONMENT='lenny-x64-base'
fi
echo "attempt to deploy environment $ENVIRONMENT"

DEPLOYED_NODES=`mktemp /tmp/"${USER}_${OAR_JOBID}_deployed_nodes_XXXXX"`

#deploy or test environnement (provided all the nodes 
# are from the same cluster) and copy public key to be able to connect to that environment
#kadeploy3 -e $ENVIRONMENT -k $KEY_FILE -f $OAR_FILE_NODES --output-ok-nodes $DEPLOYED_NODES 
kadeploy3 -a $ENVIRONMENT -k $KEY_FILE -f $OAR_FILE_NODES --output-ok-nodes $DEPLOYED_NODES 

#set common ssh and scp options
#   prevent script waiting for input with BatchMode=yes
SSH_OPTS=' -o StrictHostKeyChecking=no -o BatchMode=yes '

scriptToRun=${2%% *}
parameters=${2#* }

for node in `cat $DEPLOYED_NODES`
do 
 echo attempt to get information from $node
 ssh root@$node $SSH_OPTS cat /etc/hostname
 ssh root@$node $SSH_OPTS uname -a

 if [ $# -gt 1 ] ; then
  if [ -x "$scriptToRun" ] ; then
      #we copy the script to the node
      scp  $SSH_OPTS $scriptToRun root@$node:
      ssh $SSH_OPT root@$node ./`basename $scriptToRun` $parameters &
  else
      echo Could not find $2 to run on $node
  fi
 fi 

done

while [ 1 ]
do
	sleep 60
done

#do stuff with this deployed environment
#for node in `cat $DEPLOYED_NODES`
#do 
# echo attempt to get information from $node
# ssh root@$node $SSH_OPTS cat /etc/hostname
# ssh root@$node $SSH_OPTS uname -a
#done

#if [ $# -gt 1 ] ; then
# if [ -x "$2" ] ; then
     #we elect a head node to run the script
#     HEADNODE=`head -1 $OAR_FILE_NODES`
     #we copy the script to the headnode
#     scp  $SSH_OPTS $2 root@$HEADNODE:
#     exec ssh $SSH_OPT root@$HEADNODE ./`basename $2`
# else
#     echo Could not find $2 to run on $HEADNODE
# fi
#fi 

rm $DEPLOYED_NODES
