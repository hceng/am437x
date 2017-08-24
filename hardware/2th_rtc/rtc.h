#ifndef  __RTC_H__
#define  __RTC_H__

struct rtc_struct {
	int year;
	int month;
	int week;
	int day;
	int hour;
	int minute;
	int second;
};

extern struct rtc_struct rtc_time, rtc_alarm;

extern void rtc_start(void);
extern void rtc_stop(void);
extern void rtc_init(void);

extern int set_time(struct rtc_struct rtc_time);
extern struct rtc_struct get_time(void);
extern int set_alarm(struct rtc_struct alarm_time);
extern struct rtc_struct get_alarm(void);

#endif



