#!/bin/sh

# This is a helper script
# to create a new char-dev-driver conveniently

# error handler
error_handler() {
    echo "Usage: $0 <new module name>"
        echo "Notes: <new module name> can not be 'xxxx'"
        echo "       <new module name> should be a legal var-name in c-language"
        exit
}

# test input
if [[ $# != 1 ]]; then
    error_handler
elif [[ $1 == xxxx ]]; then
    error_handler
else
    echo $1 | egrep "^[a-zA-Z]"
    if [[ `echo $?` != 0 ]]; then
        error_handler
    elif [ -e ./${1} ]; then
        echo Module or directory exists
        error_handler
    fi
fi

NAME=$1
cp -a xxxx ${NAME}
cd ${NAME}
make clean 1&>/dev/null 2&>/dev/null
mkdir userspace
mv xxxx.c ${NAME}.c
echo sed -i \'s/xxxx/${NAME}/g\' Makefile | sh
echo sed -i \'s/xxxx/${NAME}/g\' ${NAME}.c | sh
