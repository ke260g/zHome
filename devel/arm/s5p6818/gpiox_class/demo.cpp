#include"gpiox.hpp"
#include<stdio.h>
#include<time.h>
#include<unistd.h>

#define LIGHT_TIMES 20

int main(int argc, char **argv) {
    int ret,
        i, j;

    bool val;

    gpiox gpioPort;

#if 1
    for(i = 0; i < LIGHT_TIMES; i++) {
        gpioPort.Write(GPIOD, 21, 1);
        sleep(1);

        gpioPort.Write(GPIOD, 21, 0);
        sleep(1);
    }

#else
    int read_pin_num = 30;

    for(i = 0; i < 120; i++) {
        gpioPort.Read(GPIOB, read_pin_num, &val);
        printf("GPIOD %d is %d\n", read_pin_num, val);
        printf("==========\n");

        for(j = 29; j <= 31; j++) {
            gpioPort.Read(GPIOC, j, &val);
            printf("GPIOC %d is %d\n", j, val);
        }
        getchar();
    }
#endif

    return 0;
}
