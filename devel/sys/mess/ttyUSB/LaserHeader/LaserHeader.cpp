#include"LaserHeader.hpp"

#include<time.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;

int LaserHeader::cnt = 0;
LaserHeader::LaserHeader(const int br, const char par_mode,
        const int stop_bit, const char *dev_name) {
    if(cnt > 0) {
        cnt++;
        return;
    }

    _ttyUSB_init(br, par_mode, stop_bit, dev_name);
    if(ttyUSB::success() == 0)
        cnt++;
}
int LaserHeader::success(void) {
    return ttyUSB::success();
}

LaserHeader::~LaserHeader(void) {
    if(cnt > 0)
        cnt--;
}

int LaserHeader::send_data(short delta_x, short delta_y, short cos_theta, short sin_theta) {
    if(cnt == 0)
        return -1;

    /*
    char a1 = '8';
    char b1 = '7';
    ttyUSB::_writen((&a1), 1); // higher 16 bit
    ttyUSB::_writen((&b1), 1); // lower  16 bit
    char a2 = '6';
    char b2 = '5';
    ttyUSB::_writen((&a2), 1); // higher 16 bit
    ttyUSB::_writen((&b2), 1); // lower  16 bit 
    char a3 = '4';
    char b3 = '3';
    ttyUSB::_writen((&a3), 1); // higher 16 bit
    ttyUSB::_writen((&b3), 1); // lower  16 bit
    char a4 = '2';
    char b4 = '1';
    ttyUSB::_writen((&a4), 1); // higher 16 bit
    ttyUSB::_writen((&b4), 1); // lower  16 bit
    */

    char start_byte = '0';
    ttyUSB::_writen((&start_byte), 1);

    ttyUSB::_writen(((char *)&delta_x + 1), 1); // higher 16 bit
    ttyUSB::_writen(((char *)&delta_x + 0), 1); // lower  16 bit

    ttyUSB::_writen(((char *)&delta_y + 1), 1); // higher 16 bit
    ttyUSB::_writen(((char *)&delta_y + 0), 1); // lower  16 bit

    ttyUSB::_writen(((char *)&cos_theta + 1), 1); // higher 16 bit
    ttyUSB::_writen(((char *)&cos_theta + 0), 1); // lower  16 bit

    ttyUSB::_writen(((char *)&sin_theta + 1), 1); // higher 16 bit
    ttyUSB::_writen(((char *)&sin_theta + 0), 1); // lower  16 bit

    return 0;
}

int LaserHeader::test_send(char byte) {
    return ttyUSB::_writen(&byte, 1); // higher 16 bit
}

void sig_handler(int signum) {
    cout << "LaserHeader: read() waited time out " << signum << endl;
}

int LaserHeader::recv_data(short *data, int wait_second) {
    short data_r;
    timer_t timerid;
    struct itimerspec it;
    int ret;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec = wait_second;
    it.it_value.tv_nsec = 0;

    struct sigevent evp;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);
    memset(&evp, 0, sizeof(evp));
    evp.sigev_signo = SIGUSR1;
    evp.sigev_notify = SIGEV_SIGNAL;

    timer_create(CLOCK_REALTIME, &evp, &timerid);

    timer_settime(timerid, 0, &it, NULL);
    ret = ttyUSB::_read((char *)&data_r + 1, 1);
    cout << "LaserHeader: read() return " << ret << " " << *((char *)&data_r + 1)<< endl;

    timer_settime(timerid, 0, &it, NULL);
    ret = ttyUSB::_read((char *)&data_r, 1);
    cout << "LaserHeader: read() return " << ret << " " << *((char *)&data_r) << endl;
    timer_delete(timerid);
    *data = data_r;
    cout << "data_r is " << data_r << endl;
    return 0;
}
