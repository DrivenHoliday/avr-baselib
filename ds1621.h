#ifndef DS1621_H
#define DS1621_H

#include <stdint.h>

enum ds1621_error_e
{
    DS1621_SUCESS = 0,
    DS1621_ERROR = 1
};

typedef enum ds1621_error_e ds1621_error;

typedef uint8_t ds1621_addr;

ds1621_error ds1621_init(ds1621_addr addr);

ds1621_error ds1621_start(ds1621_addr addr);

ds1621_error ds1621_read(ds1621_addr addr, float *data);

#endif
