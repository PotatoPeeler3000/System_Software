#! /bin/bash

tmpfile=$(mktemp)	#creates a temp file

echo -e "To add line numbers to file(Press 1)"
echo -e "To remove line numbers to file(Press 2)"
read input	#evauate the user input

if [ $input -eq 1 ]		#to add lines add ln(line number)
then  
	echo -e "Line numbers added!"
	nl -n ln example.txt > ${tmpfile}	#store in text in temp file
elif [ $input -eq 2 ]		#to remove lines from ln(line number)
then
	echo -e "Line numbers removed!"
	awk '{$1="";print $0}' example.txt > ${tmpfile}		#store remaining text in temp file
else
	echo "Invalid Input, please try again!"
	exit 1		#exit if input is invalid
fi
	cat ${tmpfile} > example.txt	#return stored temp file to the original
	rm -f ${tmpfile}			#remove the temp file