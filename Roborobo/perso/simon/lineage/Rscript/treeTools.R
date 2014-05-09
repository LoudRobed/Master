#countAncestors<-function(data,end,start,resolution){
#	i=length(data[,1])
#	ancestor=c()
#	allAncestor=c()
#	#i=data[data[,1]==
#	while(i > 0 && data[i,1] > start + resolution){
##		j=i
##		while(j>0 && data[j,1]>= data[i,1]-resolution  ){
#			A=data[i,2]
#			B=data[i,3]
#			if(is.element(A,ancestor)){
#				ancestor = c(B,ancestor[!is.element(ancestor,A)])
#			}
#			else{
#				ancestor=c(ancestor,B)
#			}	
#			#j=j-1
#			ancestor=unique(ancestor)
#			##print(ancestor)
#		#}
#		allAncestor=c(allAncestor,length(unique(ancestor)))
#		#ancestor=c()
#		i=i-1
#	}
#
#return(allAncestor)
#}

countAncestors<-function(data,end,start,resolution){
##notice that A is the son and B the father
	ancestors=vector("list",resolution)
	#print(resolution)
	#print(ancestors)
	nbAnc=c()
	iterations=c()
	i=length(data[,1])
	lastIt=data[i,1]
	while(i > 0 && data[i,1] >= (start*400-1) + (resolution*400)-1){
		if(data[i,1]<(lastIt-(resolution*400-1))){
			nbAnc=c(nbAnc,length(ancestors[[resolution]]))
			#names(nbAnc)=c(names(nbAnc),lastIt)
			iterations=c(iterations,lastIt)	
			lastIt=data[i,1]
			#print("oh")
			for(n in 2:resolution ){
				ancestors[[n]]=ancestors[[n-1]]
				##print(ancestors)
			}
			##print(nbAnc)
		}
		A=data[i,2]
		B=data[i,3]
		ancestors[[1]]=checkA(ancestors[[1]],A,B)
		for(n in 2:resolution ){
			
			new=check(ancestors[[n]],A,B)
			if(!is.null(new))ancestors[[n]]=new
		}
		#print(ancestors)
	
		i=i-1
	}

	return(cbind(nbAnc,iterations))
}

#This function add the father's node in the tree if he doesn't already exist
#if it exist it remplace it by the good father
checkA<-function(fathers,A,B){

	if(is.element(A,fathers)){
		fathers = c(B,fathers[!is.element(fathers,A)])
	}
	else{
		fathers=c(fathers,B)
	}	
	fathers=unique(fathers)
	
	return(fathers)
}

#This function check if the current node is in our tree
#If A is not in the tree we are checkin don't do anything, else replace
#A by is father (B) 
check<-function(fathers,A,B){

	#print(fathers)
	if(is.element(A,fathers)){
		fathers = c(B,fathers[!is.element(fathers,A)])
	}
	fathers=unique(fathers)
	
	return(fathers)
}


supprExtinction<-function(data,length){
	return ( data[is.element(data$Sim,unique(data$Sim[ data$Iteration >= length])),])
}

getGenerationBefor=function(data,max){
	j=5
	names=c()
	res=c()	
	for (i in 0:max){
		an=countAncestors(data,1,0,j)
		names=c(names,j)
		res=c(res,an[2,1])
		j = j * 2
	}

	return(cbind(names,res))
}
#
#plot(generationA[,2]~ generationA[,1],type="b",ann=F,ylim=c(0,20))> abline(h=1,col="red")
# text(0.5,1.5,"y=1",col="red")
# title(main="Number of common ancestors",xlab="Number of Previsous Generation",ylab="Number of ancestors")
