/*************************************************************************
    > File Name: led.c
    > Author: hceng
    > Description: 完善AM437X裸机LED
    > Created Time: 20170726
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"

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
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
}

void led1_on(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	GPIO5->GPIO_DATAOUT |= (0x01<<0);
}

void led1_off(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0);
}

void led2_on(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	GPIO5->GPIO_DATAOUT |= (0x01<<1);
}

void led2_off(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<1);
}

void led3_on(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	GPIO5->GPIO_DATAOUT |= (0x01<<2);
}

void led3_off(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<2);
}

void led4_on(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<0 | 0x01<<1 | 0x01<<2 | 0x01<<3);
	GPIO5->GPIO_DATAOUT |= (0x01<<3);
}

void led4_off(void)
{
	GPIO5->GPIO_DATAOUT &= ~(0x01<<3);
}

