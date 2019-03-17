#include"gpiox.hpp"
#include<stdio.h>
#include<time.h>
#include<unistd.h>

#define LIGHT_TIMES 1
#if 0
void gpiod_21_light(void) {
    int i;
    int val;
    for(i = 0; i < LIGHT_TIMES; i++) {
        val = 1;
        gpio_write(GPIOD, 21, 1);
        sleep(1);

        val = 0;
        gpio_ops(GPIOD, 21, GPIOxWRITE, &val);
        sleep(1);
    }
}
#endif

int main(int argc, char **argv) {
    int ret,
        i, j;

    bool val;

    gpiox gpioPort;
    // gpiod_21_light();
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
    return 0;
}
