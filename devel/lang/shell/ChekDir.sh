#!/bin/sh
#
# Big_Users - find big disk space users in various directories
######################################################################
# Parameters for Script 
# 
CHECK_DIRECTORIES=" /var/log /home" # directories to check
#
######################################################################
#
DATE=$(date '+%m%d%y') 				# date for report file
FILE=disk_space_$DATE.rpt
#
exec > $FILE                        # make report file STDOUT
#
echo "Top Ten Disk Space Usage" 	# report header for whole report
echo "for $CHECK_DIRECTORIES Directories"
#
for DIR_CHECK in $CHECK_DIRECTORIES # loop to du directories
do
 echo ""
 echo "The $DIR_CHECK Directories:" # Title header for each directory
#
# Create a listing of top ten disk space users
 du -Sh $DIR_CHECK 2>/dev/null |
 sort -rn |
 sed '{11,$D; =}' |
 sed '{N; s|\n|  |}' |
 gawk '{printf $1 ":" "\t" $2 "\t" $3 "\n"}'
#
done 								# end of for loop for du directories
exit
#
