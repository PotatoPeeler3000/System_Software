#! /bin/bash
echo "Enter a file name"
read input		#store input file

if [ -f ./$input ]		#if the file exists
then
	echo "Editing file!"
	mv "$input" "$(echo "$input"|sed -r 's/([^.]*)$/\L\1/'|sed -e 's/_//g')"
			#move th input file to a new one that edits the previous name
			#it removes all underscores and changes a capital JPEG to a lowercase one
else
	echo "invalid input"		#if its invalid exit and say so
	exit 1
fi