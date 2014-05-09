#! /bin/bash

rad="100" 
ants="100"
runtime="50000"
weight="0.010 0.025 0.050 0.075 0.100 0.200 0.300 0.400 0.500"
qifres="0.55"
epsilon="1"
res_dir="/home/sylvain/src/antnest/noncvs-log/roboroboAnt-test/w-ras100-UO"
res_sub_dir="w"
res_sub_sub_dir="run"
propfile="config/spikeants-current.properties"
propref="config/spikeants-batch.properties"

rm -f logs/log.txt logs/properties*.txt ant_stat.txt nest_stat.txt pot_lif.txt pot_qif.txt

make clean && make all

for a in `echo "$weight"`; do
	 rm -f "$propfile"
	 echo "run roborobo with weight = $a"
	 for i in `seq 1 10`; do
		  echo -n "$i "
		  cat "$propref" > "$propfile"
        echo "globalWeight = $a" >> "$propfile"
        echo "QifReset = $qifres" >> "$propfile"
		  echo "gMaxRadioDistance = $rad" >> "$propfile"
		  echo "gRandomSeed = $i" >> "$propfile"
		  ./roborobo -l "$propfile" > /dev/null
		  cd logs/ 
		  ./separateLogs.sh
		  cp nest_stat.txt ../../../antnest/trunk/
		  cd ../../../antnest/trunk/
		  ./post_piechart "$ants" "$runtime"
		  gnuplot create_graph.plt
		  cur_dir="$res_dir"/"$res_sub_dir"_"$a"/"$res_sub_sub_dir"_"$i"
		  mkdir -p "$cur_dir"
		  mv nest_workers.png nest_all_class.png "$cur_dir"
		  mv nest_stat.txt nest_chart.txt "$cur_dir"
		  cd ../../extern/Roborobo/
		  cp "$propfile" logs/log.txt "$cur_dir"
	 done
	 echo 
done

tmpp="tmppop.dat"
plotp="popwork.dat"

cd ../../antnest/trunk/
for a in `echo "$weight"`; do
	 rm -f "$tmpp"
	 for i in `'ls' "$res_dir"/"$res_sub_dir"_"$a" | grep $res_sub_sub_dir | sort -t "_" -k 2 -g`; do
		  if [ -d "$res_dir"/"$res_sub_dir"_"$a"/"$i" ]; then
				cp "$res_dir"/"$res_sub_dir"_"$a"/"$i"/{log,nest_stat}.txt ./
				./post_piechart "$ants" "$runtime"
				gnuplot create_graph.plt
				mv nest_workers.png nest_all_class.png "$res_dir"/"$res_sub_dir"_"$a"/"$i"/
				egrep "^STATUSAGENT" log.txt | cut -d " " -f 3- > ant_stat.txt
				egrep "^LIFAGENT" log.txt | cut -d " " -f 3- > pot_lif.txt
				egrep "^QIFAGENT" log.txt | cut -d " " -f 3- > pot_qif.txt
				gnuplot create_roboPotFocus.plt
				mv antFocused_pot-status.png "$res_dir"/"$res_sub_dir"_"$a"/"$i"/
				./post_pop_analysis "$ants" "$runtime" "$epsilon" 1>> "$tmpp"
		  fi
	 done
	 echo -ne "$a " >> "$plotp"
	 awk 'BEGIN {moy1=0;moy2=0;moy3=0;sqmoy1=0;sqmoy2=0;sqmoy3=0} {moy1+=$1; moy2+=$2;moy3+=$3;sqmoy1+=$1*$1;sqmoy2+=$2*$2;sqmoy3+=$3*$3} END{moy1/=10;moy2/=10;moy3/=10;var1=sqrt(sqmoy1/10-moy1*moy1);var2=sqrt(sqmoy2/10-moy2*moy2);var3=sqrt(sqmoy3/10-moy3*moy3);print moy1,var1,moy2,var2,moy3,var3}' "$tmpp" >> "$plotp"
done
gnuplot create_pop_work.plt

mv popwork.png "$plotp" "$res_dir"/

exit 0
