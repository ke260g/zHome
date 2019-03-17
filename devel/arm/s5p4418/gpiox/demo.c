#include"gpiox.h"
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
        i;
    ret = gpio_init();

    int val;

    // gpiod_21_light();
    int read_pin_num = 30;

    for(i = 0; i < 120; i++) {
        gpio_ops(GPIOB, read_pin_num, GPIOxREAD, &val);
        printf("GPIOD %d is %d\n", read_pin_num, val);
        sleep(1);
    }

    ret = gpio_exit();

    return 0;
}
