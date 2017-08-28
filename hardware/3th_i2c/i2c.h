
#ifndef  __I2C_H__
#define  __I2C_H__

#define GPIO_I2C
//#define REG_I2C

#ifdef GPIO_I2C

extern void i2c_init(void);
extern void eeprom_write(unsigned char addr, unsigned char data);
extern unsigned char eeprom_read(unsigned char addr);

#endif


#ifdef REG_I2C

volatile unsigned int t_count;
volatile unsigned int r_count;

volatile unsigned int num;
volatile unsigned char data_to_slave[5];
volatile unsigned char data_from_slave[5];

extern void i2c_init(void);
extern unsigned char eeprom_read(unsigned char addr);
extern void eeprom_write(unsigned char addr, unsigned char data);
extern void debug_i2c(char *str);

#endif


#endif



