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

#include"gpiox.h"

#define DEBUG 0

static int gpio_init_success_mark = 0;
static int dev_mem_fd;

/* physical address */
volatile static unsigned int GPIO_BASE_ADDR_PA = 0xC0010000;
volatile static unsigned int GPIOxBASE_OFFSET_PA[] = {
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

#define GPIOx_MAP_SIZE      (1024) // (0x64 + 0x04)

volatile static unsigned int *GPIOxBASE[5];

enum GPIOxREGS_OFFSET{
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

int gpio_init(void) {
    int i; /* common counter */
    if(gpio_init_success_mark) {
#if DEBUG
        fprintf(stderr, "gpio has already init\n");
        fprintf(stderr, "failed to %s(), line :: %d\n", __func__, __LINE__);
#endif
        return -1;
    }

    /* obtain the /dev/mem fd */
    dev_mem_fd = open("/dev/mem", O_RDWR | O_NDELAY);
    if(dev_mem_fd < 0) {

#if DEBUG
        perror("open(\"/dev/mem\")");
        fprintf(stderr, "failed to %s(), line :: %d\n", __func__, __LINE__);
#endif
        return -1;
    }

    /* map the gpiox registers address gpio [A:E]*/
    for(i = 0; i < 5; i++) {
        GPIOxBASE[i] = (unsigned int *)mmap(NULL, GPIOx_MAP_SIZE,
                PROT_READ | PROT_WRITE, MAP_SHARED, dev_mem_fd, (GPIO_BASE_ADDR_PA | GPIOxBASE_OFFSET_PA[i]));
    }
    /* check the mmap() */
    for(i = 0; i < 5; i++) {
        if(GPIOxBASE[i] == MAP_FAILED) {
#if DEBUG
            fprintf(stderr, "failed to mmap() the GPIOx address\n");
            fprintf(stderr, "failed to %s(), line :: %d\n", __func__, __LINE__);
#endif
        return -1;
        }
    }

    gpio_init_success_mark = 1;
    printf("succeed to %s()\n", __func__);

    return 0;
}

int gpio_check_init_success(const char *func_name,
        const int func_line) {
    if(!gpio_init_success_mark) {
#if DEBUG
        fprintf(stderr, "gpio did not init, needed to gpio_init()\n");
        fprintf(stderr, "failed to %s(), line :: %d\n", func_name, func_line);
#endif
        return -1;
    } else
        return 0;
}

int gpio_exit(void) {
    /* check the gpio_init() */
    if(gpio_check_init_success(__func__, __LINE__))
       return -1;

    int i; /* common couter */
    for(i = 0; i < 5; i++) {
        munmap((void *)GPIOxBASE[i], GPIOx_MAP_SIZE);
    }
    gpio_init_success_mark = 0;
    close(dev_mem_fd);
    return 0;
}

int gpio_ops(const int group,
        const int pin_num,
        const int ops_mode,
        int *value) {
    /* check the gpio_init() */
    if(gpio_check_init_success(__func__, __LINE__))
       return -1;

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
    else if(ops_mode == GPIOxWRITE)
        *value = (*value != 0); /* to make the non-zero input to `1' */

    /* set the ALTFUN to GPIO-mode */
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

int gpio_write(const int group,
        const int pin_num,
        const int value) {
    int val = value;
    return gpio_ops(group, pin_num,
            GPIOxWRITE, &val);
}

int gpio_read(const int group,
        const int pin_num,
        int *value) {
    return gpio_ops(group, pin_num,
            GPIOxREAD, value);
}
