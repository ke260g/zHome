#include"gpiox.hpp"
#include<stdio.h>
#include<time.h>
#include<unistd.h>

int ledPins[3] = {
    26, /* red */
    20, /* yellow */
    21, /* green */
};

int buttonPins[3] = {
    18, /* red */
    15, /* yellow */
    14, /* green */
};

int main(int argc, char **argv) {
    int ret,
        i, j, k;

    bool val;

    gpiox gpioPort;

    for(i = 0; i < 60; i++) {
#if 0
        for(j = 0; j < 8; j++) {
            printf("The binary number is %d.\n", j);

            for(k = 0; k < 3; k++)
                gpioPort.Write(0, ledPins[k], (j & (1 << k)));

            sleep(1);
        }
#elif 0
        gpioPort.Write(0, 20, 1);
        sleep(1);
        gpioPort.Write(0, 20, 0);
        sleep(1);
#else
        bool val;
        gpioPort.Read(0, buttonPins[0], &val);
        printf("I read %d.\n", (int)val);
        sleep(1);
#endif
    }

    return 0;

}
