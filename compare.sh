#!/bin/bash

program1=main3
program2=main5

if (( $# > 0 )); then
	FILES=$@
else
	FILES=$(ls samples | grep -E '.*\.in$')
fi


echo "$program1 $program2"
for FILE in $FILES; do
	logfilename1=${FILE/%\.in/1\.log}
	logfilename2=${FILE/%\.in/2\.log}

	./$program1 <samples/$FILE >$logfilename1
	./$program2 <samples/$FILE >$logfilename2
	
	
	result_program1=$(tail -n 2 $logfilename1 | head -n 1)
	result_program2=$(tail -n 2 $logfilename2 | head -n 1)
	time1=$(tail -n 1 $logfilename1)
	time2=$(tail -n 1 $logfilename2)

	result_test=$(cat samples/${FILE/\.in/\.out})
	
	time_avg1=$time1
	time_avg2=$time2
	let nr_tests=50
	let i=0
	
	# nr_test-1 because we've already measured once
	while (( i < nr_tests-1 )); do
		./$program1 <samples/$FILE >$logfilename1
		time_avg1=$(echo "$time_avg1 + `tail -n 1 $logfilename1`" | bc -l)
		./$program2 <samples/$FILE >$logfilename2
		time_avg2=$(echo "$time_avg2 + `tail -n 1 $logfilename2`" | bc -l)
		let i=$i+1
	done
	
	time_avg1=$(echo "$time_avg1 / $nr_tests" | bc -l)
	time_avg2=$(echo "$time_avg2 / $nr_tests" | bc -l)
	#echo "test $j:		passed in approx. $time_avg ms"
	echo "$FILE: $time_avg1 $time_avg2 `echo "100 * ($time_avg1 - $time_avg2)/$time_avg1" | bc -l`%"

	rm $logfilename1 $logfilename2
done
