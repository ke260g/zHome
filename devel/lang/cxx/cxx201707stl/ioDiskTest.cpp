/*
 * hard disk io speed test
 * only works in linux
 */
#include<fstream>
#include<iostream>
#include<ctime>
#include<cstdlib>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#include<cstdio>

using namespace std;
#define LENGTH (512*1024*1024)
#define FILENAME "__test.dat"
#define CMD_TOUCH "touch __test.dat"
#define CMD_RM "rm __test.dat"
#define LOOP_TIME (5)
char buf[LENGTH];

#define VERSION 2
int main( int argc, char **argv ) {
    double t_ms_o = 1000.0 * ((double)clock())/CLOCKS_PER_SEC;
    for(int i = 0; i < LOOP_TIME; i++) {
        system(CMD_TOUCH);
#if (VERSION == 1) /* c++ fstream */
        std::ios::sync_with_stdio(false);
        fstream * fs = new fstream;
        fs->open(FILENAME, ios::out);
        fs->write(buf, LENGTH);
        fs->close();

        fs->open(FILENAME, ios::in);
        fs->read(buf, LENGTH);
        fs->close();
        delete fs;
#elif (VERSION == 2) /* unix api, read/write */
        int fd;
        fd = open(FILENAME, O_WRONLY);
        write(fd, buf, LENGTH);
        close(fd);

        fd = open(FILENAME, O_RDONLY);
        read(fd, buf, LENGTH);
        close(fd);
#elif (VERSION == 3)
        FILE *fs;
        fs = fopen(FILENAME, "w");
        fwrite(buf, 1, LENGTH, fs);
        fclose(fs);

        fs = fopen(FILENAME, "w");
        fread(buf, 1, LENGTH, fs);
        fclose(fs);
#endif
        system(CMD_RM);
    }

    double t_ms_n = 1000.0 * ((double)clock())/CLOCKS_PER_SEC;
    cout << "r/w " << LENGTH << " bytes " << LOOP_TIME << " times, " << t_ms_n - t_ms_o << " ms\n";
    return 0;
}
