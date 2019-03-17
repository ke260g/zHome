#!/bin/sh
#
# Daily_Archive - Archive designated files & directories
#########################################################
#
# Gather Current Date
#
DATE='date +%y%m%d'
#
# Set Archive File Name
#
FILE=archive$DATE.tar.xz
#
# Set configuration and destination file
#
CONFIG_FILE=$HOME/archive/Files_To_Backup
DESTINATION=$HOME/archive/$FILE
#
############## Main Script ############################
#
# Check Backup Config file exits
#
if [ -f $CONFIG_FILE ] 			# Make sure the config file still exists.
then							# If it exists, do nothing but continue on. 
	echo			 
else							# If it doesn't exist, issue error & exit script.
	echo 
	echo "$CONFIG_FILE does not exist."
	echo "Backup not completed due to missing configuration file"
	echo 
	exit 
fi
#
# Build the names of all the files to backup
#
FILE_NO=1 						# start on line of config file.
exec < $CONFIG_FILE 			# redirect STDIN to name of config file
#
read FILE_NAME 					# read 1st record
while [ $? -eq 0 ]
do 
	# Make sure the file or directory exists
	if [ -f $FILE_NAME -o -d $FILE_NAME ]
	then 
		# if file exists, add its name to the list.
		FILE_LIST="$FILE_LIST $FILE_NAME"
	else 
		# if file doesn't not exist, issue warning
		echo 
		echo "$FILE_NAME, doesn't exist."
		echo "Obviously, I will not include it in this archive."
		echo "Continuing to build archive list..."
		echo 
	fi
#
	FILE_NO=$[$FILE_NO + 1] 	# increase line/file number by one
	read FILE_NAME				# read next record
done
#
###################################################################
#
# backup the files and  compress archive
tar -cf $DESINATION.tar $FILE_LIST 2> /dev/null
xz $DESTINATION.tar  2> /dev/null
