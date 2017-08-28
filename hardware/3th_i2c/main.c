/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: AM437X裸机i2c
    > Created Time: 20170815
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "printf.h"
#include "key.h"
#include "clkout.h"
#include "int.h"
#include "timer.h"
#include "i2c.h"

int  main()
{
    unsigned int i;
	
    uart_init();
    gic_init();
    timer2_init();
	
    i2c_init();
    printf("init ok.\n\r");

    //write eeprom.
    for(i=0; i<5; i++)
    {
        eeprom_write(i,2*i);
        delay_ms(4);//Must be delayed more than 4ms.
    }

    delay_ms(10);

    //read eeprom.
    for(i=0; i<5; i++)
    {
        printf("read_data%d = %d\n\r",i, eeprom_read(i));
        delay_ms(4);
    }

    while(1)
    {
        
    }
	
    return 0;
}




