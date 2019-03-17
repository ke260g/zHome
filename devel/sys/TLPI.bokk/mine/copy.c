/*
 * =====================================================================================
 *
 *       Filename:  copy.c
 *
 *    Description:  a more simple version "cp"
 *
 *        Version:  1.0
 *        Created:  2015年08月14日 20时45分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orona tidny (villingze), ke260g@gmail.com
 *   Organization:  IDSS
 *
 * =====================================================================================
 */

#include<sys/stat.h>
#include<fcntl.h>
#include"lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
int main(int argc, char **argv){
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    if(argc != 3 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
        usageErr("%s old-file new-file\n", argv[0]);
}
