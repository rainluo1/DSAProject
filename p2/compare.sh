#!/bin/bash

for FILE in test*.in
do
	echo Running $FILE #prints the file name (with .in)
	nFILE=`echo $FILE | cut -c -6` # remove '.in' from FILE and save it into nFILE
	./a.out < $nFILE.in > my$nFILE.out
done

for FILE in test*.out
do
	echo Comparing $FILE with my$FILE
	diff $FILE my$FILE
done
