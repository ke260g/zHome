#ifndef __GPIOX_H__
#define __GPIOX_H__


/* public interface */
/* as the @group param */
enum gpio_ops_group {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE
};

/* as the @ops_mode param */
enum gpio_ops_mode {
    GPIOxREAD,
    GPIOxWRITE
};

/*
 * gpiox::Write(), gpiox::Read
 * @group, refer to `gpio_ops_group{}'
 * @pin_num, pin_number from 0 to 31, [0:31]
 * @ops_mode, refer to gpio_ops_mode{}
 * @value,  when the `ops_mode' is GPIOxREAD,
 *          this is the output-param, to store the pin's value
 *          when the `ops_mode is GPIOxWRIDE,
 *          this is the input-param, to set the pin's output
 *          it can not be NULL
 *
 *  return value:
 *      succeed, return `0'
 *      fail, return `1'
 *
 * gpiox::Ready(),
 * to check whether init successfully
 * return value:
 *      succeed, return `0'
 *      fail, return `-1'
 */

class gpiox {
    private:
        int gpiox_ops(const int group,
                const int pin_num,
                const int ops_mode,
                bool *value);
    public:
        gpiox();
        ~gpiox();
        int Ready(void);
        int Write(const int group,
                const int pin_num,
                const bool value);
        int Read(const int group,
                const int pin_num,
                bool *value);
};
#endif
