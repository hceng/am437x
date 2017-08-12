#ifndef _AM437X_TIMER_H_
#define _AM437X_TIMER_H_
#include "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

/*DMTIMER0、DMTIMER2-11的寄存器偏移；参考芯片手册：P2767-2768*/
typedef struct {
	uint32_t TIDR;          //0h
	uint32_t RESERVED0[3];  //04H
	uint32_t TIOCP_CFG;		//10h
	uint32_t RESERVED1[3];  //14H
	uint32_t IRQ_EOI;		//20h
	uint32_t IRQSTS_RAW;	//24h
	uint32_t IRQSTS;		//28h
	uint32_t IRQEN_SET;		//2ch
	uint32_t IRQEN_CLR;		//30h
	uint32_t IRQWAKEEN;		//34h
	uint32_t TCLR;			//38h
	uint32_t TCRR;			//3ch
	uint32_t TLDR;			//40h
	uint32_t TTGR;			//44h
	uint32_t TWPS;			//48h
	uint32_t TMAR;			//4ch
	uint32_t TCAR1;			//50h
	uint32_t TSICR;			//54h
	uint32_t TCAR2;			//58h
}DMTIMER_Typedef;

/*DMTIMER1_1MS的寄存器偏移；参考芯片手册：P2799-2800*/
typedef struct {
	uint32_t TIDR;          //0h
	uint32_t RESERVED0[3];  //4h
	uint32_t TIOCP_CFG;     //10h
	uint32_t TISTAT;        //14h
	uint32_t TISR;          //18h
	uint32_t TIER;          //1ch
	uint32_t TWER;          //20h
	uint32_t TCLR;          //24h
	uint32_t TCRR;          //28h
	uint32_t TLDR;          //2ch
	uint32_t TTGR;          //30h
	uint32_t TWPS;          //34h
	uint32_t TMAR;          //38h
	uint32_t TCAR1;         //3ch
	uint32_t TSICR;         //40h
	uint32_t TCAR2;         //44h
	uint32_t TPIR;          //48h
	uint32_t TNIR;          //4ch
	uint32_t TCVR;          //50h
	uint32_t TOCR;          //54h
	uint32_t TOWR;          //58h
}DMTIMER1_Typedef;

/*SYNCTIMER的寄存器偏移；参考芯片手册：P2827*/
#define SYNCTIMER32K_SYNCNT_REV   (*(volatile unsigned int  *)(SYNCTIMER_BASE + 0x00))
#define SYNCTIMER32K_SYSCONFIG    (*(volatile unsigned int  *)(SYNCTIMER_BASE + 0x04))
#define SYNCTIMER32K_CR           (*(volatile unsigned int  *)(SYNCTIMER_BASE + 0x10))

/*WDT的寄存器偏移；参考芯片手册：P2890*/
typedef struct {
	uint32_t WIDR; 
	uint32_t RESERVED0[3]; 
	uint32_t WDSC;  
	uint32_t WDST;  
	uint32_t WISR;  
	uint32_t WIER; 
	uint32_t RESERVED1[1];   
	uint32_t WCLR;  
	uint32_t WCRR;  
	uint32_t WLDR;  
	uint32_t WTGR;  
	uint32_t WWPS;
	uint32_t RESERVED2[3];   
	uint32_t WDLY;  
	uint32_t WSPR;  
	uint32_t RESERVED3[2]; 
	uint32_t WIRQSTATRAW;  
	uint32_t WIRQSTAT;  
	uint32_t WIRQENSET;  
	uint32_t WIRQENCLR; 
}WDT1_Typedef;

/*RTC的寄存器偏移；参考芯片手册：P2842-2843*/
#define RTCSS_SECONDS_REG         (*(volatile unsigned int  *)(RTCSS_BASE + 0x00))
#define RTCSS_MINUTES_REG         (*(volatile unsigned int  *)(RTCSS_BASE + 0x04))
#define RTCSS_HOURS_REG           (*(volatile unsigned int  *)(RTCSS_BASE + 0x08))
#define RTCSS_DAYS_REG            (*(volatile unsigned int  *)(RTCSS_BASE + 0x0C))
#define RTCSS_MONTHS_REG          (*(volatile unsigned int  *)(RTCSS_BASE + 0x10))
#define RTCSS_YEARS_REG           (*(volatile unsigned int  *)(RTCSS_BASE + 0x14))
#define RTCSS_WEEKS_REG           (*(volatile unsigned int  *)(RTCSS_BASE + 0x18))
#define RTCSS_ALARM_SECONDS_REG   (*(volatile unsigned int  *)(RTCSS_BASE + 0x20))
#define RTCSS_ALARM_MINUTES_REG   (*(volatile unsigned int  *)(RTCSS_BASE + 0x24))
#define RTCSS_ALARM_HOURS_REG     (*(volatile unsigned int  *)(RTCSS_BASE + 0x28))
#define RTCSS_ALARM_DAYS_REG      (*(volatile unsigned int  *)(RTCSS_BASE + 0x2C))
#define RTCSS_ALARM_MONTHS_REG    (*(volatile unsigned int  *)(RTCSS_BASE + 0x30))
#define RTCSS_ALARM_YEARS_REG     (*(volatile unsigned int  *)(RTCSS_BASE + 0x34))
#define RTCSS_CTRL_REG            (*(volatile unsigned int  *)(RTCSS_BASE + 0x40))
#define RTCSS_STS_REG             (*(volatile unsigned int  *)(RTCSS_BASE + 0x44))
#define RTCSS_INTRS_REG           (*(volatile unsigned int  *)(RTCSS_BASE + 0x48))
#define RTCSS_COMP_LSB_REG        (*(volatile unsigned int  *)(RTCSS_BASE + 0x4C))
#define RTCSS_COMP_MSB_REG        (*(volatile unsigned int  *)(RTCSS_BASE + 0x50))
#define RTCSS_OSC_REG             (*(volatile unsigned int  *)(RTCSS_BASE + 0x54))
#define RTCSS_SCRATCH0_REG        (*(volatile unsigned int  *)(RTCSS_BASE + 0x60))
#define RTCSS_SCRATCH1_REG        (*(volatile unsigned int  *)(RTCSS_BASE + 0x64))
#define RTCSS_SCRATCH2_REG        (*(volatile unsigned int  *)(RTCSS_BASE + 0x68))
#define RTCSS_KICK0R              (*(volatile unsigned int  *)(RTCSS_BASE + 0x6C))
#define RTCSS_KICK1R              (*(volatile unsigned int  *)(RTCSS_BASE + 0x70))
#define RTCSS_REVISION            (*(volatile unsigned int  *)(RTCSS_BASE + 0x74))
#define RTCSS_SYSCONFIG           (*(volatile unsigned int  *)(RTCSS_BASE + 0x78))
#define RTCSS_IRQWAKEEN           (*(volatile unsigned int  *)(RTCSS_BASE + 0x7C))
#define RTCSS_ALARM2_SECONDS_REG  (*(volatile unsigned int  *)(RTCSS_BASE + 0x80))
#define RTCSS_ALARM2_MINUTES_REG  (*(volatile unsigned int  *)(RTCSS_BASE + 0x84))
#define RTCSS_ALARM2_HOURS_REG    (*(volatile unsigned int  *)(RTCSS_BASE + 0x88))
#define RTCSS_ALARM2_DAYS_REG     (*(volatile unsigned int  *)(RTCSS_BASE + 0x8C))
#define RTCSS_ALARM2_MONTHS_REG   (*(volatile unsigned int  *)(RTCSS_BASE + 0x90))
#define RTCSS_ALARM2_YEARS_REG    (*(volatile unsigned int  *)(RTCSS_BASE + 0x94))
#define RTCSS_PMIC                (*(volatile unsigned int  *)(RTCSS_BASE + 0x98))
#define RTCSS_DEBOUNCE            (*(volatile unsigned int  *)(RTCSS_BASE + 0x9C))

#define   DMTIMER0   		((DMTIMER_Typedef *)DMTIMER0_BASE)  
#define   DMTIMER1_1MS   	((DMTIMER1_Typedef *)DMTIMER1_1MS_BASE)  
#define   DMTIMER2   		((DMTIMER_Typedef *)DMTIMER2_BASE)  
#define   DMTIMER3   		((DMTIMER_Typedef *)DMTIMER3_BASE)  
#define   DMTIMER4   		((DMTIMER_Typedef *)DMTIMER4_BASE)  
#define   DMTIMER5   		((DMTIMER_Typedef *)DMTIMER5_BASE)  
#define   DMTIMER6   		((DMTIMER_Typedef *)DMTIMER6_BASE)  
#define   DMTIMER7   		((DMTIMER_Typedef *)DMTIMER7_BASE)  
#define   DMTIMER8  		((DMTIMER_Typedef *)DMTIMER8_BASE)  
#define   DMTIMER9   		((DMTIMER_Typedef *)DMTIMER9_BASE)  
#define   DMTIMER10  		((DMTIMER_Typedef *)DMTIMER10_BASE)  
#define   DMTIMER11  		((DMTIMER_Typedef *)DMTIMER11_BASE) 

#define   WDT1 	        	((WDT1_Typedef *)WDT1_BASE)

#if 0
/*Values that can be used while checking status received from DMTimerWritePostedStatusGet API.*/
#define DMTIMER_WRITE_POST_TMAR              (0x10)
#define DMTIMER_WRITE_POST_TTGR              (0x08)
#define DMTIMER_WRITE_POST_TLDR              (0x04)
#define DMTIMER_WRITE_POST_TCRR              (0x02)
#define DMTIMER_WRITE_POST_TCLR              (0x01)

/*Values that can be passed to DMTimerModeConfigure as timerMode.*/
#define DMTIMER_ONESHOT_CMP_ENABLE          ((0x01<<6)|~(0x01<<1))
#define DMTIMER_ONESHOT_NOCMP_ENABLE        (~(0x01<<6)|~(0x01<<1))
#define DMTIMER_AUTORLD_CMP_ENABLE          ((0x01<<6)|(0x01<<1))
#define DMTIMER_AUTORLD_NOCMP_ENABLE        (~(0x01<<6)|(0x01<<1))

/* Values that can be used to read the status obtained from WatchdogTimerWritePostedStatusGet API*/
#define WDT_WRITE_PENDING_WCLR          (0X01<<0)
#define WDT_WRITE_PENDING_WCRR          (0X01<<1)
#define WDT_WRITE_PENDING_WLDR          (0X01<<2)
#define WDT_WRITE_PENDING_WTGR          (0X01<<3)
#define WDT_WRITE_PENDING_WSPR          (0X01<<4)
#define WDT_WRITE_PENDING_WDLY          (0X01<<5)

//Values that can be passed to WatchdogTimerPreScalerClkEnable API as ptv.
#define WDT_PRESCALER_CLK_DIV_1        (0x00000000)
#define WDT_PRESCALER_CLK_DIV_2        (0x00000004)
#define WDT_PRESCALER_CLK_DIV_4        (0x00000008)
#define WDT_PRESCALER_CLK_DIV_8        (0x0000000C)
#define WDT_PRESCALER_CLK_DIV_16       (0x00000010)
#define WDT_PRESCALER_CLK_DIV_32       (0x00000014)
#define WDT_PRESCALER_CLK_DIV_64       (0x00000018)
#define WDT_PRESCALER_CLK_DIV_128      (0x0000001C)


void IntRegister(unsigned int intrNum, void (*fnHandler)(void));
void Timer2IntRegister(void);
void Timer2Config(unsigned int timerMode);
void Timer2IntEnable(void);
void Timer2Start(void);
void Timer2Stop(void);
static void Timer2Isr(void);
void setTimerCount(unsigned int count);
void clearTimerInt(void);
void DMTimerEnable(void);
void DMTimerDisable(void);
void DMTimer2WaitForWrite(unsigned char reg);

void WatchdogTimer1ModuleClkConfig(void)；
void WatchdogTimerReset(void);
void WatchdogTimerDisable(void);
unsigned int WatchdogTimerWritePostedStatusGet(unsigned int flags);
static void WatchdogTimerSetUp(void);
void WatchdogTimerPreScalerClkEnable(unsigned int ptv);
void WatchdogTimerCounterSet(unsigned int countVal);
void WatchdogTimerReloadSet(unsigned int reloadVal);
void WatchdogTimerEnable(unsigned int baseAdd);
void WatchdogTimerTriggerSet(unsigned int trigVal);
#endif

#endif
