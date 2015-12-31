#!/bin/bash

program=main4
j=0
pass=true

echo "$@"

if (( $# > 0 )); then
	FILES=$@
else
	FILES=$(ls samples | grep -E '.*\.in$')
fi

for FILE in $FILES; do
	logfilename=${FILE/%\.in/\.log}
	
	./$program <samples/$FILE >$logfilename
	
	result_program=$(tail -n 2 $logfilename | head -n 1)
	time=$(tail -n 1 $logfilename)
	result_test=$(cat samples/${FILE/\.in/\.out})
	
	if [[ $result_program != $result_test ]];
		then
			echo "test $j:		error while testing $FILE"
			echo "$result1 vs. $result2;"
			pass=false
		else
			
			time_avg=$time
			let nr_tests=10
			let i=0
			# nr_test-1 because we've already measured once
			while (( i < nr_tests-1 )); do
				./$program <samples/$FILE >$logfilename
				time_avg=$(echo "$time_avg + `tail -n 1 $logfilename`" | bc -l)
				let i=$i+1
			done
			time_avg=$(echo "$time_avg / $nr_tests" | bc -l)
			#echo "test $j:		passed in approx. $time_avg ms"
			echo $time_avg
	fi
	
	let j=$j+1
	rm $logfilename
done

echo "---------"
if [[ $pass == "true" ]];
	then
		echo "PASSED"
	else
		echo "NOT PASSED"
fi
