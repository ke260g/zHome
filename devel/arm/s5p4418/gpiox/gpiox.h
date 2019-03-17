#ifndef __GPIOX_H__
#define __GPIOX_H__


/* public interface */
/* as the `gpio_ops()' @group param */
enum gpio_ops_group {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE
};

/* as the `gpio_ops()' @ops_mode param */
enum gpio_ops_mode {
    GPIOxREAD,
    GPIOxWRITE
};

/* call it before any `gpio_ops()'
 *
 * you have to check it suceed or not.
 * once it succeeds, then you can `gpio_ops()'
 *
 * return value:
 *      succeed, return `0'
 *      fail, return `-1'
 */
int gpio_init(void);


/* call it after all the `gpio_ops()' at least once
 *
 * Once you succeed to `gpio_exit()',
 * then `gpio_ops()' can't be used.
 * If you want to `gpio_ops()' after `gpio_exit()' again,
 * just `gpio_init()' another time.
 *
 *
 * return value:
 *      succeed, return `0'
 *      fail, return `-1'
 */
int gpio_exit(void);

/*
 * `gpio_ops()' to set the gpio to the R/W mode
 * and then obtain or send the value
 *
 * @group, refer to `gpio_ops_group{}'
 * @pin_num, pin_number from 0 to 31, [0:31]
 * @ops_mode, refer to gpio_ops_mode{}
 * @value,  when the 'ops_mode' is GPIOxREAD,
 *          this is the output-param, to store the pin's value
 *          when the 'ops_mode is GPIOxWRIDE,
 *          this is the input-param, to set the pin's output
 *          it can not be NULL
 *
 *  return value:
 *      succeed, return `0'
 *      fail, return `1'
 */
int gpio_ops(const int group,
        const int pin_num,
        const int ops_mode,
        int *value);

/* the same as gpio_ops(group, pin_num, GPIOxWRIDE, ...) */
int gpio_write(const int group,
        const int pin_num,
        const int value);

/* the same as gpio_ops(group, pin_num, GPIOxREAD, ...) */
int gpio_read(const int group,
        const int pin_num,
        int *value);
#endif
