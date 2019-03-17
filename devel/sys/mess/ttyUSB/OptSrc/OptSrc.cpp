#include"OptSrc.hpp"

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<termios.h>

#include<cerrno>
#include<cstdio>
#include<cstdlib>

using namespace std;

int OptSrc::cnt = 0;

static unsigned char cmdon[7] = { 0x40, 0x05, 0x01, 0x00, 0x2A, 0xFF, 0x01 };
static unsigned char cmdoff[7] = { 0x40, 0x05, 0x01, 0x00, 0x2A, 0xFF, 0x00 };
static int cmdon_length = 7;
static int cmdoff_length = 7;

int OptSrc::Write(const unsigned char *cmd, const int length) {
    unsigned char verify = 0;
    int i;

    if(success() != 0) {
        return -1;
    }

    for(i = 0; i < length; i++) {
        ttyUSB::_writen(&cmd[i], sizeof(char));
        verify += cmd[i];
    }
    ttyUSB::_writen(&verify, sizeof(char));
    //usleep(1050 * 1000);
    return 0;
}

/* public function */
OptSrc::OptSrc(const char *dev_name) {
    if(cnt > 0) {
        cnt++;
        return;
    }
    _ttyUSB_init(19200, '0', 1, dev_name);
    if(ttyUSB::success() == 0)
        cnt++;
}

int OptSrc::success(void) {
    return ttyUSB::success();
}

OptSrc::~OptSrc() {
    if(cnt > 0)
        cnt--;
}

int OptSrc::Allon(void) {
    return Write(cmdon, cmdon_length);
}

int OptSrc::Alloff(void) {
    return Write(cmdoff, cmdoff_length);
}

void OptSrc::Ctrl_Light1(unsigned char index1,unsigned char lux1) {
    unsigned char data[7]= {0x40,0x05,0x01,0x00,0x1A,index1,lux1 };
    Write(data,7);

}

void OptSrc::Ctrl_Light2(unsigned char index1,unsigned char lux1,
        unsigned char index2,unsigned char lux2) {
    unsigned char data1[10]= {0x40,0x08,0x01,0x00,0x1A,index1,lux1,0x1A,index2,lux2 };
    Write(data1,10);
}

void OptSrc::Ctrl_Light3(unsigned char index1,unsigned char lux1,
        unsigned char index2,unsigned char lux2,
        unsigned char index3,unsigned char lux3) {
    unsigned char data1[13]= {0x40,0x0b,0x01,0x00,0x1A,index1,lux1,0x1A,index2,lux2 ,  0x1A,index3,lux3};
    Write(data1,13);
}

void OptSrc::Ctrl_Light4(unsigned char index1,unsigned char lux1,
        unsigned char index2,unsigned char lux2,
        unsigned char index3,unsigned char lux3,
        unsigned char index4,unsigned char lux4) {
    unsigned char data1[16]= {0x40,0x0e,0x01,0x00,0x1A,index1,lux1,0x1A,index2,lux2 ,  0x1A,index3,lux3,0x1A,index4,lux4};
    Write(data1,16);
}

void OptSrc::Ctrl_Light5(unsigned char index1,unsigned char lux1,
        unsigned char index2,unsigned char lux2,
        unsigned char index3,unsigned char lux3,
        unsigned char index4,unsigned char lux4,
        unsigned char index5,unsigned char lux5) {
    unsigned char data1[19]= {0x40,0x11,0x01,0x00,0x1A,index1,lux1,0x1A,index2,lux2 ,  0x1A,index3,lux3,0x1A,index4,lux4,
        0x1A,index5,lux5};
    Write(data1,19);

}


void OptSrc::Ctrl_Light6(unsigned char index1,unsigned char lux1,
        unsigned char index2,unsigned char lux2,
        unsigned char index3,unsigned char lux3,unsigned char index4,
        unsigned char lux4,unsigned char index5,unsigned char lux5,
        unsigned char index6,unsigned char lux6) {
    unsigned char data1[22]= {0x40,0x14,0x01,0x00,0x1A,index1,lux1,0x1A,index2,lux2 ,  0x1A,index3,lux3,0x1A,index4,lux4,
        0x1A,index5,lux5,0x1A,index6,lux6};
    Write(data1,22);
}
