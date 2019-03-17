/**
 * @file    test.cpp
 * @brief   functionality is none
 *
 * @version 1.1
 * @author  Darkness
 * @date    2017-10-25
 *
 * @details nothing more is details
 */
#include<iostream>

/// This macro is toolong, so comment here briefly
#define MACRO APPLY_BUG_SIZE

/**
 * @brief just a simple class for Test
 *
 * @details here is the class details\n
 *  show for fun
 */
class Test {
    public:
        int m_var; ///< simple value

        int m_color; ///< color variable

        /**
         * @brief a stupid function
         * @param a input-param set m_var
         * @param b input-param set m_color
         * @return return sum of m_var and m_color
         * @see gfunc()
         * @note a and b needs to be greater than 0
         */
        int func(int a, int b);

        /**
         * @brief a function to implement\n
         *  a more beautiful world
         * @param c input-param set m_var
         * @param d input-param set m_color
         * @return return sum of m_var and m_color
         * @see func()
         * @note c and d needs to be greater than 0
         */
        int gfunc(int c, int d);

        /**
         * @brief color enumVar
         *
         * color id constant
         */
        enum TestEnumColor{
            RED,    ///< enum, id-red
            BLUE,   ///< enum, id-blue
            GREEN,  ///< enum, id-green
        } enumVar;
};


/**
 * @brief return the bigger one
 * @param l input-param
 * @param r input-param
 * @return the bigger one of input-param
 */
int bigger(int l, int r) {
    return l > r ? l : r;
}
