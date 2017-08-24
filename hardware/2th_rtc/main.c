/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: AM437X裸机RTC
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
#include "rtc.h"

int main()
{
	rtc_time.year   = 2017;
	rtc_time.month  = 8;
	//rtc_time.week   = 1;
	rtc_time.day    = 24;
	rtc_time.hour   = 10;
	rtc_time.minute = 42;
	rtc_time.second = 15;

	rtc_alarm.year   = 2017;
	rtc_alarm.month  = 8;
	rtc_alarm.day    = 24;
	rtc_alarm.hour   = 10;
	rtc_alarm.minute = 42;
	rtc_alarm.second = 20;

	uart_init();
	printf("init ok.\n\r");

	gic_init();
	timer2_init();
	
    rtc_init();
	
	set_time(rtc_time);
	set_alarm(rtc_alarm);

	
	printf("=====set time and alarm is:=====\n\r");
	get_time();
	get_alarm();
	printf("================================\n\r");

	while(1)
	{
		delay_ms(1000);
		get_time();			
	}

	return 0;
}




