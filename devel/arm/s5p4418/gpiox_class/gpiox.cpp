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

#define GPIOx_MAP_SIZE      (1024) // (0x64 + 0x04)

static int dev_mem_fd;
static int objCounter = -1;

#if 1 /* private data */
/* physical address */
static volatile unsigned int GPIO_BASE_ADDR_PA = 0xC0010000;
static volatile unsigned int GPIOxBASE_OFFSET_PA[5] = {
    0x0000A000,     /* GPIOA */
    0x0000B000,     /* GPIOB */
    0x0000C000,     /* GPIOC */
    0x0000D000,     /* GPIOD */
    0x0000E000,     /* GPIOE */
};
/* GPIOa_BASE_PA =
 * GPIO_BASE_ADDR_PA + GPIOxBASE_OFFSET_PA[GPIOA] */
/* base virtual address */
/* GPIOxBASE[GPIOA] ==> GPIOa_BASE_PA */

static volatile unsigned int *GPIOxBASE[5];

enum GPIOxREGS_OFFSET {
    GPIOxOUT = 0,       /*  0, 0x00 */
    GPIOxOUTENB,        /*  1, 0x04 */
    GPIOxDETMODE0,      /*  2, 0x08 */
    GPIOxDETMODE1,      /*  3, 0x0c */
    GPIOxINTENB,        /*  4, 0x10 */
    GPIOxDET,           /*  5, 0x14 */
    GPIOxPAD,           /*  6, 0x18 */

    GPIOxALTFN0 = 8,     /*  8, 0x20 */
    GPIOxALTFN1,        /*  9, 0x24 */
    GPIOxDETMODEEC,     /* 10, 0x28 */

    GPIOxDETENB = 15,   /* 15, 0x3c */
    GPIOx_SLEW,         /* 16, 0x40 */
    GPIOx_SLEW_DISABLE, /* 17, 0x44 */
    GPIOx_DRV1,         /* 18, 0x48 */
    GPIOx_DRV1_DISABLE, /* 19, 0x4c */
    GPIOx_DRV0,         /* 20, 0x50 */
    GPIOx_DRV0_DISABLE, /* 21, 0x54 */
    GPIOx_PULLSEL,      /* 22, 0x58 */
    GPIOx_PULLSEL_DISABLE_DEFAULT, /* 23, 0x5c */
    GPIOx_PULLENB,      /* 24, 0x60 */
    GPIOx_PULLENB_DISABLE_DEFAULT, /* 25, 0x64*/
};
#endif

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

    /* obtain the /dev/mem fd */
    dev_mem_fd = open("/dev/mem", O_RDWR | O_NDELAY);
    if(dev_mem_fd < 0) {
        perror("failed to init gpiox,  open(\"/dev/mem\")");
        return;
    }

    /* map the gpiox registers address gpio [A:E]*/
    for(i = 0; i < 5; i++) {
        GPIOxBASE[i] =
            (unsigned int *)mmap(NULL, GPIOx_MAP_SIZE,
                    PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem_fd,
                    (GPIO_BASE_ADDR_PA | GPIOxBASE_OFFSET_PA[i]));
    }
    /* check the mmap() */
    for(i = 0; i < 5; i++) {
        if(GPIOxBASE[i] == MAP_FAILED) {
            printf("failed to init gpiox,  mmap() the GPIOx address error\n");
            return;
        }
    }
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
        int i; /* common couter */
        for(i = 0; i < 5; i++)
            munmap((void *)GPIOxBASE[i], GPIOx_MAP_SIZE);
        objCounter = -1;
        close(dev_mem_fd);
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

    /* check the input-param valid */
    if(group != GPIOA &&
            group != GPIOB &&
            group != GPIOC &&
            group != GPIOD &&
            group != GPIOE)
        return -1;
    if(pin_num > 31 || pin_num < 0)
        return -1;
    if(value == NULL)
        return -1;
    if(ops_mode != GPIOxREAD && ops_mode != GPIOxWRITE)
        return -1;

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
        /* enable the pull-up resistance */
        *(GPIOxBASE[group] + GPIOx_PULLSEL) |= (1 << pin_num);
        *(GPIOxBASE[group] + GPIOx_PULLSEL_DISABLE_DEFAULT) |= (1 << pin_num);
        *(GPIOxBASE[group] + GPIOx_PULLENB) |= (1 << pin_num);
        *(GPIOxBASE[group] + GPIOx_PULLENB_DISABLE_DEFAULT) |= (1 << pin_num);

        /* disable the output, which means the input */
        *(GPIOxBASE[group] + GPIOxOUTENB) &= ~(1 << pin_num);

        *value = ((*(GPIOxBASE[group] + GPIOxPAD) & (1 << pin_num)) != 0);
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
