#if 0
target public interface
gpio_ops(int group,     [A:E]
        int pin,        [0:31]
        int ops_mode,   [Read,Write]
        int *value);    /* output-param as the pin's value when ops == R,
                         * input-param as the pin's value when ops == W */
#endif

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/mman.h>

#include"gpiox.hpp"


/* have to install the wiringPi lib on raspberry pi */
#include<wiringPi.h>

static int dev_mem_fd;
static int objCounter = -1;

/* <<== real operate function == >> */
/* perform real initialize */
static void __gpiox_init() {
    int i; /* common counter */
    if(getuid() != 0) {
        printf("gpiox failed to init, must run as root.\n");
        return;
    }
    if(objCounter > 0) {
        objCounter++;
        printf("gpiox init successfully.\n");
        return;
    }

    if(wiringPiSetupGpio())
        return;

    /* first object init successfully. */
    objCounter = 1;
    printf("gpiox init successfully.\n");
}

/* perform real release */
static void __gpiox_exit() {
    /* check init successfully */
    if(objCounter == -1) {
        printf("gpiox does not init successfully, nothing to release.\n");
        return;
    }

    /* check the objCounter */
    if (objCounter > 0)
        objCounter--;

    if (objCounter == 0) {
        /* perform real release */
            /* do nothing */;
        objCounter = -1;
        printf("gpiox has been release.\n");
    }
}

static int __gpiox_ops(const int group,
        const int pin_num,
        const int ops_mode,
        bool *value) {
    /* check init) */
    if(objCounter <= 0) {
        printf("gpiox does not init successfully, failed to access gpio port.\n");
        return -1;
    }

#if 0 /* raspberry do not have the gpio pins group */
    /* check the input-param valid */
    if(group != GPIOA &&
            group != GPIOB &&
            group != GPIOC &&
            group != GPIOD &&
            group != GPIOE)
        return -1;
#else
#endif

    // if(pin_num > 31 || pin_num < 0)
    if(pin_num > 31 || pin_num < 0)
        return -1;
    if(value == NULL)
        return -1;
    if(ops_mode != GPIOxREAD && ops_mode != GPIOxWRITE)
        return -1;

#if  0
    /* set the ALTFUN to GPIO-mode, refer to s5p4418 manual */
    if(pin_num > 15)
        *(GPIOxBASE[group] + GPIOxALTFN1) &= ~(3 << ((pin_num - 16) * 2));
    else
        *(GPIOxBASE[group] + GPIOxALTFN0) &= ~(3 << (pin_num * 2));

    /* perform GPIOxWRITE */
    if(ops_mode == GPIOxWRITE) {
        unsigned int tmp;
        /* enable the output */
        *(GPIOxBASE[group] + GPIOxOUTENB) |= (1 << pin_num);

        /* clear the output bit */
        tmp = (*(GPIOxBASE[group] + GPIOxOUT) & ~(1 << pin_num));

        /* set the output value */
        tmp |= (*value << pin_num);
        *(GPIOxBASE[group] + GPIOxOUT) = tmp;
    }

    /* perform GPIOxREAD */
    if(ops_mode == GPIOxREAD) {
        /* disable the output, which means the input */
        *(GPIOxBASE[group] + GPIOxOUTENB) &= ~(1 << pin_num);

        *value = ((*(GPIOxBASE[group] + GPIOxPAD) & (1 << pin_num)) != 0);
    }
#endif

	pullUpDnControl(pin_num, PUD_UP);
    /* perform GPIOxWRITE */
    if(ops_mode == GPIOxWRITE) {
        pinMode(pin_num, OUTPUT); // set mode to output
        digitalWrite(pin_num, *value); // write
    }

    /* perform GPIOxREAD */
    if(ops_mode == GPIOxREAD) {
        pinMode(pin_num, INPUT);
        *value = digitalRead(pin_num);
    }
    return 0;
}

static int __gpiox_write(const int group,
        const int pin_num,
        const bool value) {
    bool val = value;
    return __gpiox_ops(group, pin_num,
            GPIOxWRITE, &val);
}

static int __gpiox_read(const int group,
        const int pin_num,
        bool *value) {
    return __gpiox_ops(group, pin_num,
            GPIOxREAD, value);
}

static int __gpiox_ready(void) {
    return (objCounter >= 0 ? 1 : 0);
}
/* >>== real operate function ==<< */

/* <<== gpiox-class-wrapper, for cpp ==>> */
gpiox::gpiox() {
    __gpiox_init();
}

gpiox::~gpiox() {
    __gpiox_exit();
}
/* >>== gpiox-class-wrapper, for cpp ==<< */
int gpiox::gpiox_ops(const int group,
        const int pin_num,
        const int ops_mode,
        bool *value) {
    return __gpiox_ops(group, pin_num, ops_mode, value);
}

int gpiox::Write(const int group,
        const int pin_num,
        const bool value) {
    return __gpiox_write(group, pin_num, value);
}

int gpiox::Read(const int group,
        const int pin_num,
        bool *value) {
    return __gpiox_read(group, pin_num, value);
}

int gpiox::Ready(void) {
    return __gpiox_ready();
}
/* >>== gpiox-class-wrapper, for cpp ==<< */
