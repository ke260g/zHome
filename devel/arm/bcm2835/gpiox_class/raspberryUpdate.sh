#!/bin/bash
# shell script run on the raspberry
# update the dir

remote_host="192.168.3.13"
local_dir="."
remote_files="rc/devel/sys/Mess/gpiox_bcm2835/*"

if [[ `pwd | sed "s|^.*\/||"` != gpiox_bcm2835 ]]
then
    echo not in the right directory.
    exit 1
fi

if [[ `uname -n` == gentoo ]]
then
    echo not on the right arch.
    exit 1
fi

echo start to update the repos

rm -f * # delete all the old files in local dir

while true; do
    ncftpget -u ll ${remote_host} ${local_dir} ${remote_files}
    if [[ `echo $?` != 0 ]]; then
    echo try again
    else
        break
    fi
done
chmod u+x ${0}
