#ifndef _AM437X_GPIO_H_
#define _AM437X_GPIO_H_
//#include  "AM437X_GPIO.h"
#include "AM437X_DataType.h"

/*GPIO的寄存器偏移；参考芯片手册：P3715*/
typedef struct {
	uint32_t 			GPIO_REVISION;              //0h 	 
	uint32_t 			RESERVED0[3];  		  		//4h  (10h-4h=16-4=12除4=3)         
	uint32_t 			GPIO_SYSCONFIG; 			//10h 
	uint32_t 			RESERVED1[3];  		  		//14h 
	uint32_t 			GPIO_EOI; 					//20h 
	uint32_t 			GPIO_IRQSTS_RAW_0;			//24h 
	uint32_t 			GPIO_IRQSTS_RAW_1; 		    //28h 
	uint32_t 			GPIO_IRQSTS_0; 				//2Ch 
	uint32_t 			GPIO_IRQSTS_1;				//30h 
	uint32_t 			GPIO_IRQSTS_SET_0; 		    //34h 
	uint32_t 			GPIO_IRQSTS_SET_1; 		    //38h 
	uint32_t 			GPIO_IRQSTS_CLR_0; 		    //3Ch 
	uint32_t 			GPIO_IRQSTS_CLR_1; 		    //40h 
	uint32_t 			GPIO_IRQWAKEN_0; 			//44h 
	uint32_t 			GPIO_IRQWAKEN_1; 			//48h 
	uint32_t 			RESERVED2[50]; 		  		//4Ch （114h-4ch=c8h=200除4=50）
	uint32_t 			GPIO_SYSSTS;				//114h
	uint32_t 			RESERVED3[6];  		  		//118h（130h-118h=18h=24除4=6）
	uint32_t 			GPIO_CTRL;					//130h
	uint32_t 			GPIO_OE;					//134h
	uint32_t 			GPIO_DATAIN; 				//138h
	uint32_t 			GPIO_DATAOUT;				//13Ch
	uint32_t 			GPIO_LEVELDETECT0; 		    //140h
	uint32_t 			GPIO_LEVELDETECT1; 		    //144h
	uint32_t 			GPIO_RISINGDETECT; 		    //148h
	uint32_t 			GPIO_FALLINGDETECT; 		//14Ch
	uint32_t 			GPIO_DEBOUNCEN; 			//150h
	uint32_t 			GPIO_DEBOUNCINGTIME; 	    //154h
	uint32_t 			RESERVED4[14];  		  	//158h（190h-158h=38h=56除4=14） 
	uint32_t 			GPIO_CLRDATAOUT; 			//190h
	uint32_t 			GPIO_SETDATAOUT; 			//194h
}GPIO_Typedef;

#define   GPIO0  	    ((volatile GPIO_Typedef *)GPIO0_BASE)  
#define   GPIO1  	    ((volatile GPIO_Typedef *)GPIO1_BASE)  
#define   GPIO2  	    ((volatile GPIO_Typedef *)GPIO2_BASE)  
#define   GPIO3  	    ((volatile GPIO_Typedef *)GPIO3_BASE)  
#define   GPIO4  	    ((volatile GPIO_Typedef *)GPIO4_BASE)  
#define   GPIO5  	    ((volatile GPIO_Typedef *)GPIO5_BASE)  

#define 	GPIO1_OE          	(*(volatile unsigned long *)(GPIO1_BASE + 0x134) )
#define 	GPIO1_CLRDATAOUT  	(*(volatile unsigned long *)(GPIO1_BASE + 0x190) )
#define 	GPIO1_SETDATAOUT  	(*(volatile unsigned long *)(GPIO1_BASE + 0x194) )


/*
4412实现为：
#define ICDSPI_STATUS  (* (volatile icdspi_status *)0X10490D04 )
在volatile前面加了一个*，从而访问时就是ICDSPI_STATUS.xxx

*/

/*
解决sourcinsight无法通过->来操作。
NVIC_Type  * const nvic = ((NVIC_Type *) NVIC_BASE);

*/
#endif


