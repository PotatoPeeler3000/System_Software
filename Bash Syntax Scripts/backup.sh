#! /bin/bash
echo "Enter a file/directory: "
read input

if [ -d $input ] || [ -e $input ]	#check to see if file exists
then
	mv $input .backup/	#move it into the backup directory
	cd .backup/		#move into backup directory

	if [ ! -d ./$input.backup ] && [ ! -e ./$input.backup ]		#check to see if backup is made
	then	
		echo "Backing up files/directory now..."	
		cp  $input $input.backup		#copy file to .backup file
		mv $input ..			#move file back out of backup directory
	else
		echo "Can't backup, file/directory already there!"
	fi
else
	echo "File/directory doens't exist"		#file doesn't exist'
fi