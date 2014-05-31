#!/bin/bash

echo "Cleaning after PBS"

SSH_OPTS=' -o StrictHostKeyChecking=no -o BatchMode=yes '

for node in `cat nodes-s`
do
	echo $node
#	./helloworld/helloworld
	ssh $SSH_OPTS andhag@$node "killall -9 roborobo ; killall -9 runParallal.sh" &
	#ssh $SSH_OPTS jeanmarm@$node  echo "pouf" &
done

