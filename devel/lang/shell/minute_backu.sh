#!/bin/zsh 
# time var #

MONTH=`date +%m`
DATE=`date +%d`
HOURtmp=`date +%k`
HOUR=`printf %-d $HOURtmp`
MINUTE=`date +%M`

DEST_DIR=$HOME/backupbasedir 			# directory name
CONFIG_FILE=$DEST_DIR/dirlist		# backup dir list 
DEST_FILE=$DEST_DIR/${MONTH}m/${DATE}th/${HOUR}h/${HOUR}:${MINUTE}.tar

# directory #
mkdir -p $DEST_DIR/${MONTH}m/${DATE}th/${HOUR}h 

# SRC_DIR
SRC_DIR=`awk 'BEGIN{RS="\n"; ORS=","} {print $0}' $CONFIG_FILE | sed 's/^/\{/ ; s/.$/\}/'`

tar cf $DEST_FILE $SRC_DIR

