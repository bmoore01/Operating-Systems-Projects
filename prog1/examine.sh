#!/usr/bin/bash

source '/usr/lib/smartlog/smartlog.sh'


# check if a file has been passed to the script
if [ $# -eq 1 ]
then
		toCompile=$1
else
	tip "C or Java source file needed"
fi

# get the extension of the file passed
name=$(basename "$toCompile")
extension="${name##*.}"

# is the file a C file?
if [ "$extension" == "c" ]
then
		tip "C file found"
		# get the filename without the C extension
		shortName=$(basename $toCompile .c)
		
		# start compiling the program
		log "Compiling $toCompile"
		if gcc $toCompile -o $shortName; then
				ok
				tip "compilation succeeded attempting to run"
				./$shortName
		else
				fail
				log "compilation failed"
				fail
				die "Resolve compilation errors and try again"
		fi

elif [ "$extension" == "java" ]
then
		tip "Java file found"
		shortName=$(basename $toCompile .java)
		log "Compiling $toCompile"
		if javac $toCompile; then
				ok
				tip "compilation succeeded attempting to run"
				java $shortName
		else
				fail
				log "compilation failed"
				fail
				die "Resolve compilation errors and try again"
		fi
else
	die "No compatible file found, use a java or C file"
fi
