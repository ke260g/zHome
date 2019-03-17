#ifndef TTYUSB_HPP
#define TTYUSB_HPP

#define ttyUSB_PAR_NONE (0) // parity none
#define ttyUSB_PAR_ODD (1) // parity odd
#define ttyUSB_PAR_EVEN (2) // partiy even

#include<sys/types.h>
class ttyUSB {
private:
    int fd;
public:
    ttyUSB();
    ~ttyUSB();
protected:
    /* @brief pure virtual function, to make ttyUSB must be inheritted */
    virtual void pvf(void) = 0;

    /* @brief refer ttyUSB_init() @ref ttyUSB */
    int _ttyUSB_init(const int br, const char par_mode,
                     const int stop_bit, const char * dev_name);

    /* @brief refer writen() @ref writen */
    int _writen(const void *buf, size_t count);

    /* @brief refer readn() @ref readn */
    int _readn(void *buf, size_t count);

    /* @brief refer man 2 read */
    int _read(void *buf, size_t count);

    /* @brief refer error_msg @ref error_msg */
    void _error_msg(const char *s);

    /* @brief return 0 if fd is valid , or -1 if fd is invalid */
    int success(void);
};

#endif /* TTYUSB_HPP */
