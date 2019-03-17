#include<cstdlib>
#include<cstdio>
using namespace std;

#include"../ttyUSB.hpp"
#include"XK3190.hpp"

int XK3190::cnt = 0; // instance counter
#define STR_LENGTH (8)
/*
 * one-bit for sign, indicate positive or negetive
 * six-bit for digit
 * one-bit for dot
 * last-bit for '\0'
 */

XK3190::XK3190(const char *dev_name) {
    if(cnt > 0) {
        cnt++;
        return;
    }
    /*
     * refer to the electronic weight scales manual
     * baud rate: 9600
     * none parity
     * one stop bit
     */

    _ttyUSB_init(9600, '0', 1, dev_name);
    if(ttyUSB::success() == 0)
        cnt++;
}

XK3190::~XK3190(void) {
    if(cnt > 0)
        cnt--;
}

int XK3190::success(void) {
    return ttyUSB::success();
}

int XK3190::get_weight(double *weight) {
    int ret;
    double f_weight;
    char str_weight[STR_LENGTH];

    if(cnt == 0)
        return -1;

    ret = _readn(str_weight, (STR_LENGTH - 1));
    str_weight[STR_LENGTH] = '\0';

    printf("%s", str_weight);
    if(str_weight[0] == '-')
        f_weight = -atof(str_weight + 1);
    else
        f_weight = atof(str_weight);
    *weight = f_weight;
    return 0;
}
