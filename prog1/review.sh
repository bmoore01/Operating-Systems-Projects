#!/usr/bin/bash

source '/usr/lib/smartlog/smartlog.sh'

# global variable delceration
file=README.rst

# has the script been passed a directory
if [ $# -eq 1 ]
then
		cd $1
else
	tip "No directory argument passed, using the current directory"
fi

# check if README.rst exists in the directory
if [ -f "$file" ]
then
		tip "README.rst found"
else
		die "README.rst not found, aborting script"
fi

# search for the filenames in README.rst
fileNames=($(grep -Eoh "\w+\.rst" $file))

for file in ${fileNames[@]} 
do
	cat -n $file
	read -p "$*"
	clear
done

