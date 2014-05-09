#! /bin/bash

# rad=`seq 40 80 800`
# weight=`seq 0.01 0.01 0.2`
# rad=`seq 80 80 800`
rad=`seq 80 80 800`
weight=`seq 0.02 0.02 0.2`
ants="100"
runtime="50000"
qifres="0.55"
epsilon="1"
seed="0"

resd="/home/sylchev/src/antnest/noncvs-log/roborobo/emergence-efficiency-Forage1000"
#resd="/users/tao/sylchev/noncvs-log/emergence-rd-w-UO"
resdd="p"
resddd="w"
resdddd="run"

propfile="config/spikeants-current.properties"
propref="config/spikeants-batch.properties"

cd logs
./clean-logs.sh
rm -f ant_stat.txt nest_stat.txt nest_forage.txt nest_foragingtime.txt pot_lif.txt pot_qif.txt properties_*.txt
cd ..

# make clean && make all

#######################################################################
# Pour reprendre un run stoppe en cours
# currad="240"
# curweight=`seq 0.09 0.01 0.1`

# p="240"
# w="0.08"
# curi="4"
# echo -ne "Continuing run p=$p w=$w i=$curi : "
# for i in `seq "$curi" 10`; do
# 	 echo -n "."
# 	 rm -f "$propfile"
# 	 cat "$propref" > "$propfile"
# 	 echo "globalWeight = $w" >> "$propfile"
# 	 echo "QifReset = $qifres" >> "$propfile"
# 	 echo "gMaxRadioDistance = $p" >> "$propfile"
# 	 echo "gRandomSeed = $i" >> "$propfile"
# 	 echo "gAgentRegistration = true" >> "$propfile"
# 	 ./roborobo -l "$propfile" > /dev/null
# 	 cd logs/ 
# 	 ./separateLogs.sh
# 	 # gnuplot ../../../antnest/trunk/create_graph.plt
# 	 cur_dir="$resd"/"$resdd"_"$p"/"$resddd"_"$w"/"$resdddd"_"$i"
# 	 mkdir -p "$cur_dir"
# 	 # mv nest_workers.png  "$cur_dir"
# 	 mv nest_foragingtime.txt nest_forage.txt nest_stat.txt "$cur_dir"
# 	 cd ..
# done
# cd "$resd"/"$resdd"_"$p"/"$resddd"_"$w"
# gnuplot /home/sylchev/src/antnest/trunk/create_graph_multiplot.plt
# cd -

# for p in `echo "$currad"`; do
# 	 for w in `echo "$curweight"`; do 
# 		  echo -ne "\nCalculating r= $p and w= $w :"
# 		  for i in `seq 1 10`; do
# 				echo -n "."
# 				rm -f "$propfile"
# 				cat "$propref" > "$propfile"
# 				echo "globalWeight = $w" >> "$propfile"
# 				echo "QifReset = $qifres" >> "$propfile"
# 				echo "gMaxRadioDistance = $p" >> "$propfile"
# 				echo "gRandomSeed = $i" >> "$propfile"
# 				echo "gAgentRegistration = true" >> "$propfile"
# 				./roborobo -l "$propfile" > /dev/null
# 				cd logs/ 
# 				./separateLogs.sh
# 				# gnuplot ../../../antnest/trunk/create_graph.plt
# 				cur_dir="$resd"/"$resdd"_"$p"/"$resddd"_"$w"/"$resdddd"_"$i"
# 				mkdir -p "$cur_dir"
# 	         # mv nest_workers.png  "$cur_dir"
# 				mv nest_foragingtime.txt nest_forage.txt nest_stat.txt "$cur_dir"
# 				cd ..
# 		  done
# 		  cd "$resd"/"$resdd"_"$p"/"$resddd"_"$w"
# 		  gnuplot /home/sylchev/src/antnest/trunk/create_graph_multiplot.plt
# 		  cd -
# 	 done
# done
#######################################################################

# Premier run sans communication
# p="0"
# w="0.00"

# cat "$propref" > "$propfile"
# echo "globalWeight = $w" >> "$propfile"
# echo "QifReset = $qifres" >> "$propfile"
# echo "gMaxRadioDistance = $p" >> "$propfile"
# echo "gRandomSeed = $seed" >> "$propfile"
# echo "gAgentRegistration = true" >> "$propfile"
# tail -n 30 "$propfile"
# echo "##########################"
# echo -ne "\nCalculating r= $p and w= NULL :"

# ./roborobo -l "$propfile" > /dev/null

# cd logs/ 
# ./separateLogs.sh
# mv nest_stat.txt nest_forage.txt nest_foragingtime.txt ../../../antnest/trunk/
# cd ../../../antnest/trunk/
# # ./post_piechart "$ants" "$runtime" && cp nest_chart.txt 
# gnuplot create_graph.plt

# for w in `echo "$weight"`; do 
# 	 for i in `seq 1 10`; do
# 		  cur_dir="$resd"/"$resdd"_"$p"/"$resddd"_"$w"/"$resdddd"_"$i"
# 		  mkdir -p "$cur_dir"
# 		  cp nest_workers.png "$cur_dir"
# 		  cp nest_stat.txt nest_forage.txt nest_foragingtime.txt "$cur_dir"
# 	 done
# done
# cd ../../extern/Roborobo/
# cp "$propfile" "$resd"

#########################################################################
# # real work begins !
# for p in `echo "$rad"`; do
# 	 for w in `echo "$weight"`; do 
# 		  echo -ne "\nCalculating r= $p and w= $w :"
# 		  for i in `seq 1 10`; do
# 				echo -n "."
# 				rm -f "$propfile"
# 				cat "$propref" > "$propfile"
# 				echo "globalWeight = $w" >> "$propfile"
# 				echo "QifReset = $qifres" >> "$propfile"
# 				echo "gMaxRadioDistance = $p" >> "$propfile"
# 				echo "gRandomSeed = $i" >> "$propfile"
# 				echo "gAgentRegistration = true" >> "$propfile"
# 				./roborobo -l "$propfile" > /dev/null
# 				cd logs/ 
# 				./separateLogs.sh
# 				# mv nest_stat.txt nest_forage.txt ../../../antnest/trunk/
# 				# cd ../../../antnest/trunk/
# 				# ./post_piechart "$ants" "$runtime"
# 				# gnuplot create_graph.plt
# 				# gnuplot ../../../antnest/trunk/create_graph.plt
# 				cur_dir="$resd"/"$resdd"_"$p"/"$resddd"_"$w"/"$resdddd"_"$i"
# 				mkdir -p "$cur_dir"
# 				# mv nest_workers.png  "$cur_dir"
# 				mv ant_collision.txt nest_foragingtime.txt nest_forage.txt nest_stat.txt "$cur_dir"
# 				cd ..
# 				# cd ../../extern/Roborobo/
# 		  done
# 		  cd "$resd"/"$resdd"_"$p"/"$resddd"_"$w"
# 		  gnuplot /home/sylchev/src/antnest/trunk/create_graph_multiplot.plt
# 		  cd -
# 	 done
# done

# # rad=`seq 0 80 800`
tmplog2="temp2.log"
tmplog="temp.log"
tmpe="tmpentropy.dat"
tmpf="tmpforagingtime.dat"
tmpd="tmpdirectentropy.dat"
tmpeff="tmpeffort.dat"
# tmpc="tmpcollision.dat"
em="emergence-entropy.dat"
emd="emergence-directentropy.dat"
ploteff="emergence-effort.dat"
emf="emergence-meanforagingtime.dat"
# emc="emergence-collision.dat"

cd ../../antnest/trunk/
rm -f "$em" "$emd" "$emf" "$ploteff" "$emc"
# (( a = 0 ))

for p in `echo "$rad"`; do
	 # (( b = 0 ))
	 for w in `echo "$weight"`; do 
		  rm -f "$tmpe" "$tmpf" "$tmpd" "$tmpeff" "$tmpc"
		  for i in `seq 1 10`; do
				echo "begin ant $p w $w run $i"
				cur_dir="$resd"/"$resdd"_"$p"/"$resddd"_"$w"/"$resdddd"_"$i"
				# cp "$cur_dir"/nest_stat.txt ./
				# ./post_pop_analysis "$ants" "$runtime" "$epsilon" 1> "$tmplog2" 2>> "$tmpe"
				awk 'BEGIN {moy1=0} {moy1+=$2} END{moy1/=50000;print moy1}' "$cur_dir"/nest_forage.txt >> "$tmpeff"
				awk '{print $3}' "$cur_dir"/nest_stat.txt | sort -n | uniq -c | sort -n -b -r | awk '{entropy+=-($1/50000)*log($1/50000)} END {print entropy}' >> "$tmpd"
				awk -v tot=`wc -l "$cur_dir"/nest_foragingtime.txt | cut -d " " -f 1` '{if ($2!=0){moy+=$2; sqmoy+=$2*$2;suc++}} END{persuc=suc/tot; moy/=tot; var=sqrt(sqmoy/tot-moy*moy); print persuc,moy,var}' "$cur_dir"/nest_foragingtime.txt >> "$tmpf"
				# cat ant_collision.txt >> "$tmpc"

				# awk -v tot=`wc -l "$cur_dir"/nest_foragingtime.txt | cut -d " " -f 1` '{moy+=$2; sqmoy+=$2*$2} END{moy/=tot; var=sqrt(sqmoy/tot-moy*moy); print moy,var}' "$cur_dir"/nest_foragingtime.txt >> "$tmpf"
		  done
	 	  # cat "$tmpe"
	 	  # vale=`awk 'BEGIN {moy1=0;sqmoy1=0} {moy1+=$1;sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpe"`
	 	  # echo "$p $w $vale" >> "$em"
	 	  vald=`awk 'BEGIN {moy1=0;sqmoy1=0} {moy1+=$1;sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpd"`
	 	  echo "$p $w $vald" >> "$emd"
	 	  valeff=`awk 'BEGIN {moy1=0;sqmoy1=0;} {moy1+=$1; sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpeff"`
	 	  echo "$p $w $valeff" >> "$ploteff"
	 	  valf=`awk 'BEGIN {moy1=0;sqmoy1=0;moy2=0;sqmoy2=0;} {moy1+=$1; sqmoy1+=$1*$1;moy2+=$2; sqmoy2+=$2*$2;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);moy2/=10;var2=sqrt(sqmoy2/10-moy2*moy2);print moy1,var1,moy2,var2}' "$tmpf"`
	 	  # valf=`awk 'BEGIN {moy1=0;sqmoy1=0;} {moy1+=$1; sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpf"`
	 	  echo "$p $w $valf" >> "$emf"
		  # valc=`awk 'BEGIN {moy1=0;sqmoy1=0;} {moy1+=$1; sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpc"`
		  # echo "$p $w $valf" >> "$emc"
	 # 	  # (( b++ ))
	 done
	 # echo >> "$em"
	 echo >> "$emd"
	 echo >> "$emf"
	 echo >> "$ploteff"
	 # echo >> "$emc"
	 # (( a++ ))
done
echo "did you change param_ant.txt in antnest for post_pop_analysis?"
# cp "$em" "$ploteff" "$emc"  "$resd"/
cp "$emf" "$emd" "$ploteff" "$resd"/
cd "$resd"
gnuplot /home/sylchev/src/antnest/trunk/create_emergence.plt
cd -

exit 0
