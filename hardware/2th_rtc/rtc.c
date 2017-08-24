/*************************************************************************
    > File Name: rtc.c
    > Author: hceng
    > Description: 完善AM437X裸机RTC
    > Created Time: 20170823
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "delay.h"
#include "printf.h"
#include "int.h"
#include "rtc.h"

struct rtc_struct rtc_time, rtc_alarm;

void rtc_start(void)
{
	RTCSS->CTRL |= (0x01<<0);
}

void rtc_stop(void)
{
	RTCSS->CTRL &= ~(0x01<<0);
}

static void rtc_int_enalbe(void)
{
	RTCSS->INTRS |= (0x01<<3);//RTC_ALARM1
}

static void rtc_int_clear(void)
{
	RTCSS->STS |= (0x01<<6);;//RTC_ALARM1
}

void alarm_irq(void)
{
	rtc_int_clear();
	printf("\n\r----------------alarm_irq-----------------\n\r");
}

void rtc_init(void)
{
	//1.set performing the System Clock configuration for RTC.
	PRCM_CM_RTC_CLKCTRL &= ~(0x3<<0);
	PRCM_CM_RTC_CLKCTRL |= (0x01<<1);
 
	PRCM_CM_RTC_CLKSTCTRL &= ~(0x3<<0);

	//Wait write is completed.
	while(!(PRCM_CM_RTC_CLKSTCTRL & (0x01<<9 | 0x01<<8)));
	while(PRCM_CM_RTC_CLKCTRL & (0x03<<16));

	//2.Enable the RTC module;
	RTCSS->CTRL &= ~(0x01<<6);

	//3.Write Project Disable;
	RTCSS->KICK0R = (0x83E70B13);
	RTCSS->KICK1R = (0x95A4F1E0);

	//4.Set clock Source;
	//mode1:Internal clock 
	RTCSS->OSC &= ~(0x01<<3);
	RTCSS->OSC |=  (0x01<<6);
	//mode2:External clock 
	//RTCSS->OSC &= ~(0x01<<3);
	//RTCSS->OSC |=  (0x01<<6 | 0x01<<3);	

	register_irq(RTCALARMINT, alarm_irq);

	interrupt_init(RTCALARMINT);

	//5.Enable interrupt;
	//RTCSS->INTRS &= ~(0x03<<0); 
	//RTCSS->INTRS |= (0x01<<3);//RTC_ALARM1
	rtc_int_enalbe();
	
	//6.Run.
	//RTCSS->CTRL |= (0x01<<0);
	//rtc_start();
}

int set_time(struct rtc_struct rtc_time)
{
	rtc_stop();
	
	if((rtc_time.year-2000) > 99 || (rtc_time.year-2000) < 0)
		goto err;
	RTCSS->YEARS = (((rtc_time.year-2000)/10) << 4) | (((rtc_time.year-2000)%10) << 0);

	if(rtc_time.month > 12 || rtc_time.month < 0)
		goto err;
	RTCSS->MONTHS = ((rtc_time.month/10) << 4) | ((rtc_time.month%10) << 0);

	if(rtc_time.week > 7 || rtc_time.week < 0)
		//goto err;
		rtc_time.week = 1;
	RTCSS->WEEKS = rtc_time.week;

	if(rtc_time.day > 32 || rtc_time.day < 0)
		goto err;
	RTCSS->DAYS = ((rtc_time.day/10) << 4) | ((rtc_time.day%10) << 0);	

	if(rtc_time.hour > 23 || rtc_time.hour < 0)
		goto err;
	RTCSS->HOURS = ((rtc_time.hour/10) << 4) | ((rtc_time.hour%10) << 0);

	if(rtc_time.minute > 59 || rtc_time.minute < 0)
		goto err;
	RTCSS->MINUTES = ((rtc_time.minute/10) << 4) | ((rtc_time.minute%10) << 0);

	if(rtc_time.second > 59 || rtc_time.second < 0)
		goto err;
	RTCSS->SECONDS = ((rtc_time.second/10) << 4) | ((rtc_time.second%10) << 0);

	rtc_start();
	
	return 0;
	
err:
	printf("set_time err.\n\r");
	return 1;
}

struct rtc_struct get_time(void)
{
	struct rtc_struct current_time;
	
	current_time.year   = (((RTCSS->YEARS   & (0x03<<4))>>4)*10 + (RTCSS->YEARS   & (0x0F<<0)));
	current_time.month  = (((RTCSS->MONTHS  & (0x07<<4))>>4)*10 + (RTCSS->MONTHS  & (0x0F<<0)));
	current_time.week   = (  RTCSS->WEEKS   & (0x0F<<0));	
	current_time.day    = (((RTCSS->DAYS    & (0x07<<4))>>4)*10 + (RTCSS->DAYS    & (0x0F<<0)));
	current_time.hour   = (((RTCSS->HOURS   & (0x03<<4))>>4)*10 + (RTCSS->HOURS   & (0x0F<<0)));
	current_time.minute = (((RTCSS->MINUTES & (0x07<<4))>>4)*10 + (RTCSS->MINUTES & (0x0F<<0)));
	current_time.second = (((RTCSS->SECONDS & (0x07<<4))>>4)*10 + (RTCSS->SECONDS & (0x0F<<0)));

	printf("\n\rcurrent_time is:\n\r\%d-%d-%d %d:%d:%d\n\r",\
current_time.year+2000,current_time.month,current_time.day,current_time.hour,current_time.minute,current_time.second);

	return current_time;
}

int set_alarm(struct rtc_struct alarm_time)
{
	if((alarm_time.year-2000) > 99 || (alarm_time.year-2000) < 0)
		goto err;
	RTCSS->ALARM_YEARS = (((alarm_time.year-2000)/10) << 4) | (((alarm_time.year-2000)%10) << 0);

	if(alarm_time.month > 12 || alarm_time.month < 0)
		goto err;
	RTCSS->ALARM_MONTHS = ((alarm_time.month/10) << 4) | ((alarm_time.month%10) << 0);
	
	if(alarm_time.day > 32 || alarm_time.day < 0)
		goto err;
	RTCSS->ALARM_DAYS = ((alarm_time.day/10) << 4) | ((alarm_time.day%10) << 0);	
	
	if(alarm_time.hour > 23 || alarm_time.hour < 0)
		goto err;
	RTCSS->ALARM_HOURS = ((alarm_time.hour/10) << 4) | ((alarm_time.hour%10) << 0);
	
	if(alarm_time.minute > 59 || alarm_time.minute < 0)
		goto err;
	RTCSS->ALARM_MINUTES = ((alarm_time.minute/10) << 4) | ((alarm_time.minute%10) << 0);
	
	if(alarm_time.second > 59 || alarm_time.second < 0)
		goto err;
	RTCSS->ALARM_SECONDS = ((alarm_time.second/10) << 4) | ((alarm_time.second%10) << 0);
	
		return 0;
		
	err:
		printf("set_alarm err.\n\r");
		return 1;

}
struct rtc_struct get_alarm(void)
{
	struct rtc_struct alarm_time;
	
	alarm_time.year   = (((RTCSS->ALARM_YEARS   & (0x03<<4))>>4)*10 + (RTCSS->ALARM_YEARS   & (0x0F<<0)));
	alarm_time.month  = (((RTCSS->ALARM_MONTHS  & (0x07<<4))>>4)*10 + (RTCSS->ALARM_MONTHS  & (0x0F<<0)));
	alarm_time.day    = (((RTCSS->ALARM_DAYS    & (0x07<<4))>>4)*10 + (RTCSS->ALARM_DAYS    & (0x0F<<0)));
	alarm_time.hour   = (((RTCSS->ALARM_HOURS   & (0x03<<4))>>4)*10 + (RTCSS->ALARM_HOURS   & (0x0F<<0)));
	alarm_time.minute = (((RTCSS->ALARM_MINUTES & (0x07<<4))>>4)*10 + (RTCSS->ALARM_MINUTES & (0x0F<<0)));
	alarm_time.second = (((RTCSS->ALARM_SECONDS & (0x07<<4))>>4)*10 + (RTCSS->ALARM_SECONDS & (0x0F<<0)));

	printf("\n\ralarm_time is:\n\r\%d-%d-%d %d:%d:%d\n\r",\
	alarm_time.year+2000,alarm_time.month,alarm_time.day,alarm_time.hour,alarm_time.minute,alarm_time.second);

	return alarm_time;
}



