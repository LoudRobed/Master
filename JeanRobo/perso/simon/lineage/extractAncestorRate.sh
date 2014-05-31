

#!/bin/bash

start=$1
end=$2
dirname=$3
step=$4
if [ ! -d "ancestorsRawData" ]; then
	mkdir ancestorsRawData
	echo "---"
	echo
	echo
	echo
fi

for i in $(ls $dirname/datalog_*.txt); do
    bname=`basename $i .txt`
    echo $i
    ./toNewick.py -F $i -B $start -E $end -N 0 -S $step
    cat ./ancestorsRawData/$bname.csv | awk -v step="$step" 'BEGIN{FS=","}{print $101","$102","NR*step}' > ./ancestorsRawData/$bname.csved
done
# paste -d',' *.csved > all.csv
echo "NbAliveT,SoucheT-1,G" > _head

endDirName=`basename $dirname`

cat _head ./ancestorsRawData/*.csved > ./ancestorsRawData/$endDirName.csv
rm _head

