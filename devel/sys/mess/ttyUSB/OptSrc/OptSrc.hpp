#ifndef __OPTSRC_HPP__
#define __OPTSRC_HPP__

#include"../ttyUSB.hpp"

/* control wodepu optical source */

class OptSrc : public ttyUSB {
    private:
        void pvf() { }; // must implement this function for ttyUSB
        static int cnt; // instaance counter

        int Write(const unsigned char *cmd, const int length);

    public:
        OptSrc(const char *dev_name = "/dev/ttyUSB0");
        ~OptSrc();

        /* @brief return 0 if hardware initialize successfully,
         *      or -1 if an error occurred */
        int success(void);

        int Allon(void);

        int Alloff(void);

        void Ctrl_Light1(unsigned char index1,unsigned char lux1);

        void Ctrl_Light2(unsigned char index1,unsigned char lux1,
                unsigned char index2,unsigned char lux2);

        void Ctrl_Light3(unsigned char index1,unsigned char lux1,
                unsigned char index2,unsigned char lux2,
                unsigned char index3,unsigned char lux3);

        void Ctrl_Light4(unsigned char index1,unsigned char lux1,
                unsigned char index2,unsigned char lux2,
                unsigned char index3,unsigned char lux3,
                unsigned char index4,unsigned char lux4);

        void Ctrl_Light5(unsigned char index1,unsigned char lux1,
                unsigned char index2,unsigned char lux2,
                unsigned char index3,unsigned char lux3,
                unsigned char index4,unsigned char lux4,
                unsigned char index5,unsigned char lux5);

        void Ctrl_Light6(unsigned char index1,unsigned char lux1,
                unsigned char index2,unsigned char lux2,
                unsigned char index3,unsigned char lux3,unsigned char index4,
                unsigned char lux4,unsigned char index5,unsigned char lux5,
                unsigned char index6,unsigned char lux6);
};
#endif

#if 0 /* usage */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main( int argc, char **argv ) {
    OptSrc obj;
    if(obj.success() != 0) {
        fprintf(stderr, "Device not found\n");
        return -1;
    }
    for(int i = 0; i < 10; i++) {
        obj.Allon();
        sleep(2);
        obj.Alloff();
    }

    obj.Ctrl_Light1(0, 240);
    return 0;
}
#endif
