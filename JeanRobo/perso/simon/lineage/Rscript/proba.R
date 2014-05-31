###This function was used to calcul a strange thing
#In fact it create a new table with a step=step*2
#not sure if it always works 
getProba<-function(data,step){
    res= matrix(nrow=0,ncol=3)

    for (g in 2:(max(data[,3])-step)){
	    res=rbind(res,cbind(data[data[,3]== g + step,1],data[data[,3] == g,2],g))
    }
    
    return(res)
}


#DEPRECATED
parseData<-function(file){
	data = read.csv(file)
	data$G = data$G-1
	return(cbind((1-data$NbAliveT/data$SoucheT.1),data$G))
}
#DEPRECATED
drawBoxplot<-function(data,inf,sup){
     boxplot(data[data[,2]>inf & data[,2]<sup,1]~data[data[,2]>inf & data[,2]<sup,2],outline=F)
     abline(v=ceiling(length(unique(data[data[,2]>inf & data[,2]<sup,2]))/2),col="red")
}




####
#DEPRECATED
#Function with the aim to build up a table with
getAllAncestor<-function(mydata,start,end,before){
  allancestor=matrix(nrow=2001,ncol=100)

  for(g in start:end){   #foreach generations wanted
	print(g)
      ancestor=c()
      for(r in 1:100){   #for each robots 
      
	
	ancestor = mydata[g,r] 
	if(mydata[g,r]>-1){
	    for(b in 1:before){
		    
		    ancestor = mydata[g-(b-1),ancestor + 1]
	    }
	}
	allancestor[g,r]= ancestor
	
    }
 }
 
  return(allancestor)
}



backMore<-function(a,inf,sup, ... ){
#TODO : add some space between max and end of graph
    we=boxplot((a[a[,3]>inf & a[,3]<sup,1]/a[a[,3]>inf & a[,3]<sup,2])~a[a[,3]>inf & a[,3]<sup,3],outline=F,...)
    abline(v=which(we$names == "1000"),col="red")
   return(we)

}

#########################
trace<-function(data,inf,sup,step,...){
    tcls=.2

#set marges, font size...
    par(cex=2,cex.main=1,mgp=c(1.5,0.5,0),oma=c(0,0,0,0),mar=c(3,3,3,3),font.main=1)


#print the graph
res=backMore(data,inf,sup,ann=F,main=paste("Ancestors per generation (b=",step,")",sep=""),xlab="Iterations",ylab="#ancestors (normalized)",axes=F,...)


vat=seq(1,length(res$names),17)
hat=seq(.0,1,.10)

axis(3,at=vat,rep("",length(vat)),tcl=tcls,lwd=0,lwd.ticks=1)
axis(1,at=vat,label=format(as.numeric(res$names)*400,scientific=F)[vat] ,tcl=tcls,lwd=0,lwd.ticks=1)

#Comput min and max of absisse axis
mina=min(res$out[res$out != -Inf])-.1
maxa=max(res$out[res$out != +Inf])+.1
#draw absisse axis
axis(2,hat,tcl=tcls,lwd=0,lwd.ticks=1)
axis(4,hat,rep("",length(hat)),tcl=tcls,lwd=0,lwd.ticks=1)
box()
return(res)
}
#########################
divByStep<-function(data,step){
	a=data
	a[,3]=a[,3]/step
	return(a)
}


#######################################
#main

main<-function(name,begin,end,step){

test=read.csv(name)

test=divByStep(test,step)

if(!file.exists("./images/")){ dir.create("./images/")}
prefix=strsplit(basename(name),"\\.")[[1]][1]
print(prefix)
postscript(file=paste("./images/",prefix,"_commonAncestorPerGenerationB",step,"_G",begin,"toG",end,".eps",sep=""), height=25,width=10,family="Times")

 oui=trace(test,begin,end,step)
dev.off()
}
#######################################

#To type "updt()" in place of "source("proba.R")"
updt<-function(){source("./proba.R")}

cmd_args = commandArgs(TRUE); #used to parse commande line arguments (arguments given after the -args)
name = cmd_args[1]
start = cmd_args[2]
end = cmd_args[3]
step = cmd_args[4]
print (step)
if(start<1)start = 1

main(name,as.integer(start),as.integer(end),as.integer(step))

