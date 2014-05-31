#An R script loaded automatically in R using :
#	R --vanilla CMD BATCH /home/simon/evorob/Dev/Roborobo/perso/simon/lineage/Rscript/autoR.R ;
# 	

#get extracted Dataz


data=read.csv("logs_genometracking.csv")
data_active=read.csv("logs_actives.csv")

source("~/evorob/Dev/Roborobo/perso/simon/lineage/Rscript/plotg.R")
#drawAllGraph(data,data_active,col=F)
#drawAllFixed(data)
writeAliveGraphForAllSpars(data_active)
