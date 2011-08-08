#include "ds1621.h"

#include <util/delay.h>

#include "i2cmaster.h" 

#define DS1621_ADDR (0b10010000)
#define MAKE_ADDR(addr) (DS1621_ADDR + addr*10) //FALSCH!!!
#define DO(cmd) if(cmd) { return DS1621_ERROR; }

ds1621_error ds1621_init(ds1621_addr addr)
{
    i2c_init();

    i2c_start_wait(MAKE_ADDR(addr)+I2C_WRITE);
    DO(i2c_write(0xee));
    i2c_stop();
}

ds1621_error ds1621_start(ds1621_addr addr)
{
    i2c_start_wait(MAKE_ADDR(addr)+I2C_WRITE);
    DO(i2c_write(0xac));
    DO(i2c_write(0x0));
    i2c_stop();
    _delay_ms(11);
    
    return DS1621_SUCESS;
}

ds1621_error ds1621_read(ds1621_addr addr, float *data)
{
    int8_t   datah = 0;
    uint8_t  datal = 0, count_remain = 0, count_per_c = 0;

    i2c_start_wait(MAKE_ADDR(addr)+I2C_WRITE);
    DO(i2c_write(0xaa));
    DO(i2c_rep_start(MAKE_ADDR(addr)+I2C_READ));
    datah = i2c_readNak();
    datal = i2c_readNak();
    i2c_stop();
    
    i2c_start_wait(MAKE_ADDR(addr)+I2C_WRITE);
    DO(i2c_write(0xa8));
    DO(i2c_rep_start(MAKE_ADDR(addr)+I2C_READ));
    count_remain = i2c_readNak();
    i2c_stop();
    
    i2c_start_wait(MAKE_ADDR(addr)+I2C_WRITE);
    DO(i2c_write(0xa9));
    DO(i2c_rep_start(MAKE_ADDR(addr)+I2C_READ));
    count_per_c = i2c_readNak();
    i2c_stop();
    
    if(data)
    {
        *data = (float)datah - 0.25f + (((float)(count_per_c-count_remain)) / ((float)(count_per_c)));
    }
    
    return DS1621_SUCESS;
}
