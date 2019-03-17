#ifndef LASERHEADER
#define LASERHEADER

#include"../ttyUSB.hpp"
#define DEFAULT_DEVICE ("/dev/ttyUSB0")
#define DEFAULT_BAUDRATE (9600)

/* send data to fpga, to control LaserHeader */

class LaserHeader : public ttyUSB {
private:
    void pvf() { }; // must implement this function
    static int cnt; // instance counter

public:
    /* @brief initialize rs232 communicate with fpga
     *      to control LaserHeader
     * @param br baud rate, supports 9600, 19200, 115200
     * @param parity mode, '0' means none,
     *      '1' means odd, '2' means even
     * @param stop_bit 1 means one bit, 2 means two bits
     * @param dev_name device name
     */
    LaserHeader(const int br = DEFAULT_BAUDRATE,
            const char par_mode = '0', const int stop_bit = 1,
            const char *dev_name = DEFAULT_DEVICE);
    ~LaserHeader();

    /* @brief return 0 if hardware initialize successfully,
     *      or -1 if an error occurred */
    int success(void);

    /* @brief send delta x, delta y, theta */
    int send_data(short delta_x, short delta_y, short cos_theta, short sin_theta);

    /* @brief receive data
     * @param data to restore read data
     * @param wait_second as its name
     */
    int recv_data(short *data, int wait_second = 2);

    int test_send(char byte);
};


#endif /* LASERHEADER */

#if 0 /* usage example, uncomment to be a demo */

// demo
#include<iostream>
using std::cout;
using std::endl;
int main(int argc, char **argv) {
    LaserHeader obj;
    if(obj.success() != 0) {
        cout << "hardware error occurred" << endl;
        return -1;
    }
    obj.test_send();
    return 0;
}
#endif /* 0 */
