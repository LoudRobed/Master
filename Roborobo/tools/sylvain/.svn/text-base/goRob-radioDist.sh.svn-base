#! /bin/bash

rad=`seq 0 160 800`
ants="100"
runtime="50000"
weight="0.005"
qifres="0.55"
epsilon="1"
res_dir="/home/sylchev/src/antnest/noncvs-log/roborobo/radio-efficiency-F541-w0.1"
#res_dir="/users/tao/sylchev/noncvs-log/rd-w0.2-UO-noCollision"
res_sub_dir="rd"
res_sub_sub_dir="run"
propfile="config/spikeants-current.properties"
propref="config/spikeants-batch.properties"

# cd logs
# ./clean-logs.sh
# rm -f ant_stat.txt nest_stat.txt nest_forage.txt pot_lif.txt pot_qif.txt
# cd ..

# make clean && make all

# for a in `echo "$rad"`; do
# 	 rm -f "$propfile"
# 	 echo "run roborobo with radio dist = $a"
# 	 for i in `seq 1 10`; do
# 		  echo -n "$i "
# 		  cat "$propref" > "$propfile"
#         echo "globalWeight = $weight" >> "$propfile"
#         echo "QifReset = $qifres" >> "$propfile"
# 		  echo "gMaxRadioDistance = $a" >> "$propfile"
# 		  echo "gRandomSeed = $i" >> "$propfile"
# 		  echo "gAgentRegistration = true" >> "$propfile"
# 		  ./roborobo -l "$propfile" > /dev/null
# 		  cd logs/ 
# 		  ./separateLogs.sh
# 		  # cp nest_stat.txt ../../../antnest/trunk/
# 		  # cd ../../../antnest/trunk/
# 		  # ./post_piechart "$ants" "$runtime"
# 		  # gnuplot create_graph.plt
# 		  cur_dir="$res_dir"/"$res_sub_dir"_"$a"/"$res_sub_sub_dir"_"$i"
# 		  mkdir -p "$cur_dir"
# 		  # mv nest_workers.png "$cur_dir"
# 		  mv nest_foragingtime.txt nest_forage.txt nest_stat.txt "$cur_dir"
# 		  cd ..
# 		  # cp "$propfile" logs/log.txt logs/nest_forage.txt "$cur_dir"
# 	 done
# 	 echo 
# 	 cd "$res_dir"/"$res_sub_dir"_"$a"
# 	 gnuplot /home/sylchev/src/antnest/trunk/create_graph_multiplot.plt
# 	 cd -
# done
# cp "$propfile" "$res_dir"/

tmpp="tmppop.dat"
tmpe="tmpeffort.dat"
tmpf="tmpforagingtime.dat"
tmpd="tmpdirectentropy.dat"
plotp="popwork.dat"
plote="popeffort.dat"
emd="directentropy.dat"
emf="meanforagingtime.dat"

cd ../../antnest/trunk/
rm -f "$plotp $plote $emd $emf" 
for a in `echo "$rad"`; do
	 rm -f "$tmpp" "$tmpf" "$tmpe"
	 for i in `'ls' "$res_dir"/"$res_sub_dir"_"$a" | grep $res_sub_sub_dir | sort -t "_" -k 2 -g`; do
		  if [ -d "$res_dir"/"$res_sub_dir"_"$a"/"$i" ]; then
				cur_dir="$res_dir"/"$res_sub_dir"_"$a"/"$i"
				cp "$cur_dir"/nest_stat.txt ./
				# ./post_piechart "$ants" "$runtime"
				# gnuplot create_graph.plt
				# mv nest_workers.png nest_all_class.png "$res_dir"/"$res_sub_dir"_"$a"/"$i"/
				# gnuplot create_roboPotFocus.plt
				# mv antFocused_pot-status.png "$res_dir"/"$res_sub_dir"_"$a"/"$i"/
				./post_pop_analysis "$ants" "$runtime" "$epsilon" 1>> "$tmpp"
				# TODO mettre le runtime a la place de 50000
				awk 'BEGIN {moy1=0} {moy1+=$2} END{moy1/=50000;print moy1}' nest_forage.txt >> "$tmpe"
				awk '{print $3}' "$cur_dir"/nest_stat.txt | sort -n | uniq -c | sort -n -b -r | awk '{entropy+=-($1/50000)*log($1/50000)} END {print entropy}' >> "$tmpd"
				awk -v tot=`wc -l "$cur_dir"/nest_foragingtime.txt | cut -d " " -f 1` '{if ($2!=0){moy+=$2; sqmoy+=$2*$2;suc++}} END{persuc=suc/tot; moy/=tot; var=sqrt(sqmoy/tot-moy*moy); print persuc,moy,var}' "$cur_dir"/nest_foragingtime.txt >> "$tmpf"
		  fi
	 done
	 echo -ne "$a " >> "$plotp"
	 awk 'BEGIN {moy1=0;moy2=0;moy3=0;sqmoy1=0;sqmoy2=0;sqmoy3=0} {moy1+=$1; moy2+=$2;moy3+=$3;sqmoy1+=$1*$1;sqmoy2+=$2*$2;sqmoy3+=$3*$3} END{moy1/=10;moy2/=10;moy3/=10;var1=sqrt(sqmoy1/10-moy1*moy1);var2=sqrt(sqmoy2/10-moy2*moy2);var3=sqrt(sqmoy3/10-moy3*moy3);print moy1,var1,moy2,var2,moy3,var3}' "$tmpp" >> "$plotp"
	 echo -ne "$a " >> "$plote"
	 awk 'BEGIN {moy1=0;sqmoy1=0;} {moy1+=$1; sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpe" >> "$plote"
	 vald=`awk 'BEGIN {moy1=0;sqmoy1=0} {moy1+=$1;sqmoy1+=$1*$1;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);print moy1,var1}' "$tmpd"`
	 echo "$a $vald" >> "$emd"
	 valf=`awk 'BEGIN {moy1=0;sqmoy1=0;moy2=0;sqmoy2=0;} {moy1+=$1; sqmoy1+=$1*$1;moy2+=$2; sqmoy2+=$2*$2;} END{moy1/=10;var1=sqrt(sqmoy1/10-moy1*moy1);moy2/=10;var2=sqrt(sqmoy2/10-moy2*moy2);print moy1,var1,moy2,var2}' "$tmpf"`
	 echo "$a $valf" >> "$emf"
done
gnuplot create_pop_work.plt

mv popwork.png popeffort.png "$plotp" "$plote" "$emd" "$emf" "$res_dir"/

exit 0
