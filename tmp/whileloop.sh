#!/bin/bash
COUNTER=0
while [ $COUNTER -lt 10 ]
do
	echo the counter is $COUNTER
	COUNTER=$(( $COUNTER+1 ))
	echo Now the conter is $COUNTER
done
