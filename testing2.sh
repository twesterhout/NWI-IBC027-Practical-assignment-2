#!/bin/bash

program=main3
i=0
pass=true


for FILE in $(ls samples | grep -E '.*\.in$'); do
	logfilename=${FILE/%\.in/\.log}
	
	cat samples/$FILE | ./$program > $logfilename
	
	result1=$(tail -n 2 $logfilename | head -n 1)
	result2=$(cat samples/${FILE/\.in/\.out})
	
	if [[ $result1 != $result2 ]];
		then
			echo "test $i:	error while testing $FILE"
			echo "$result1 vs. $result2;"
			pass=false
		else
			echo "test $i:	passed in $(cat $logfilename | tail -n 1) ms"
	fi
	
	let i=$i+1
	rm $logfilename
done

echo "---------"
if [[ $pass == "true" ]];
	then
		echo "PASSED"
	else
		echo "NOT PASSED"
fi
