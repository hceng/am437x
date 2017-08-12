/*************************************************************************
    > File Name: led.c
    > Author: hceng
    > Description: 完善AM437X裸机LED
    > Created Time: 20170726
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"

//针对哪个板子，就只打开哪个宏；
#define TI_BOARD   0
//#define MYIR_BOARD 0

#ifdef  TI_BOARD

void led_init(void)
{
	//1.使能GPIO外设时钟. CP468
	PRCM_CM_PER_GPIO5_CLKCTRL  = (0x01<<1);//CP511

	//2.设置4个GPIO模式、使能上/下拉、关闭输入、设置上拉;CP642
	CTRL_CONF_UART3_RXD  &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_UART3_RXD  |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_UART3_TXD  &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_UART3_TXD  |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_UART3_RTSN &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_UART3_RTSN |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉
	CTRL_CONF_UART3_CTSN &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);//使能上/下拉、关闭输入
	CTRL_CONF_UART3_CTSN |=  (0x7<<0 | 0x01<<17);//IO模式，设置上拉

	//3.设置为输出;CP3731
	GPIO5->GPIO_OE &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);

	//4.设置允许输出位;
	GPIO5->GPIO_SETDATAOUT |= (0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);

}


void led_on(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT |= (0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
}

void led_off(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
}

void led1_on(void)
{
	//先清;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT |= (0x01<<0);
}

void led1_off(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0);
}

void led2_on(void)
{
	//先清;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT |= (0x01<<1);
}

void led2_off(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<1);
}

void led3_on(void)
{
	//先清;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT |= (0x01<<2);
}

void led3_off(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<2);
}

void led4_on(void)
{
	//先清;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT |= (0x01<<3);
}

void led4_off(void)
{
	//5.设置输出值;
	GPIO5->GPIO_DATAOUT &= ~(0x01<<3);
}
#endif



#ifdef  MYIR_BOARD
void  led_on(void)
{
	//am437x手册140的CM_PER，468页、507页
	PRCM_CM_PER_GPIO1_CLKCTRL  = (2);
	//等待bit[17-16]=0,
	//简单起见，先延时
	delay(5000);

	CTRL_CONF_GPMC_A8  = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A9  = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A10 = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);
	CTRL_CONF_GPMC_A11 = ( (0x1<<25) | (0x0<<18) | (0x1<<16) | (0x7<<0));//(0x02010007);	

	//GPIO1_OE = (0xFEFFFFFF);//bit24=1
	GPIO1_SETDATAOUT = (0xFFFFFFFF);
    GPIO1_OE &=~((1<<27) | (1<<26)  | (1<<25)  | (1<<24));
	
	//while(1)
	{
		//
		//GPIO1_CLRDATAOUT = (0x01000000);
		GPIO1_CLRDATAOUT = (1<<24);//gpio1_24
		delay(500000);
		//while(1);
		//GPIO1_SETDATAOUT = (0x01000000);
		GPIO1_SETDATAOUT = (1<<24);//gpio1_24
		delay(500000);

		GPIO1_CLRDATAOUT = (1<<25);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<25);//gpio1_24
		delay(500000);	

		GPIO1_CLRDATAOUT = (1<<26);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<26);//gpio1_24
		delay(500000);	

		GPIO1_CLRDATAOUT = (1<<27);//gpio1_24
		delay(500000);
		GPIO1_SETDATAOUT = (1<<27);//gpio1_24
		delay(500000);			
	}

}

void  led_off()
{
	GPIO1_SETDATAOUT |=  (1<<24);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<25);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<26);//gpio1_24
	GPIO1_SETDATAOUT |=  (1<<27);//gpio1_24
}

void led1_on()
{
	GPIO1_CLRDATAOUT |=  (1<<24);//gpio1_24
}

void led1_off()
{
	GPIO1_SETDATAOUT |=  (1<<24);//gpio1_24
}

void led2_on()
{
	GPIO1_CLRDATAOUT |=  (1<<25);//gpio1_24
}

void led2_off()
{
	GPIO1_SETDATAOUT |=  (1<<25);//gpio1_24
}

void led3_on()
{
	GPIO1_CLRDATAOUT |= (1<<26);//gpio1_24
}

void led3_off()
{
	GPIO1_SETDATAOUT |= (1<<26);//gpio1_24
}

void led4_on()
{
	GPIO1_CLRDATAOUT |=  (1<<27);//gpio1_24
}

void led4_off()
{
	GPIO1_SETDATAOUT |=  (1<<27);//gpio1_24
}
#endif
	
