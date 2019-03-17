#ifndef XK3190_HPP
#define XK3190_HPP

#include"../ttyUSB.hpp"
#define DEFAULT_DEVICE ("/dev/ttyUSB0")

/* to control electronic weight scales, XK3190 with USB-RS232*/
class XK3190 : public ttyUSB {
private:
    void pvf() { }; // must implement this function
    static int cnt; // instance counter
public:
    XK3190(const char *dev_name = DEFAULT_DEVICE);
    ~XK3190();

    /* @brief return 0 if fd is valid , or -1 if fd is invalid */
    int success(void);
    /*
     * @brief get the weight from the electronic weighter
     *    block until obtain the weight or error occurs
     * @param weight an output parameter to restore weight
     * @return return 0 if succeed or -1 if error occurs
     */
    int get_weight(double *weight);
};

#endif /* XK3190_HPP */

#if 0
/* usage example, uncomment to be a demo */
#include<iostream>
using std::endl;
using std::cout;

int main(void) {
    double weight;
    XK3190 ins("/dev/uart1");

    if(ins.success() != 0) {
        cout << "failed to initialize, check the hardware state" << endl;
        return -1;
    }

    for(int i = 0; i < 30; i++) {
        if(ins.get_weight(&weight) == 0) {
            cout << "Weight is " << weight << endl;
        } else {
            cout << "error occurs" << endl;
        }
    }
    return 0;
}
#endif
