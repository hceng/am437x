#ifndef _AM437X_ADC_H_
#define _AM437X_ADC_H_

#include "AM437X_DataType.h"
#include  "AM437X_Mapping.h"


/*ADC0的寄存器偏移；参考芯片手册：P1797_1798*/
typedef struct {
	uint32_t REVISION;  		      //0h
	uint32_t RESERVED0[3];  		  //4h
	uint32_t SYSCONFIG; 			  //10h
	uint32_t RESERVED1[4];  		  //14h
	uint32_t IRQSTS_RAW; 			  //24h
	uint32_t IRQSTS; 				  //28h
	uint32_t IRQEN_SET;				  //2Ch
	uint32_t IRQEN_CLR;               //30h 
	uint32_t IRQWAKEUP;               //34h
	uint32_t DMAEN_SET;               //38h
	uint32_t DMAEN_CLR;               //3Ch
	uint32_t CTRL;                    //40h
	uint32_t ADCSTAT;                 //44h  
	uint32_t ADCRANGE;                //48h 
	uint32_t ADC_CLKDIV;              //4Ch 
	uint32_t ADC_MISC;                //50h 
	uint32_t STEPEN;                  //54h 
	uint32_t IDLECONFIG;              //58h  
	uint32_t TS_CHARGE_STEPCONFIG;    //5Ch 
	uint32_t TS_CHARGE_DELAY;         //60h 
	uint32_t STEPCONFIG_0;            //64h 
	uint32_t STEPDELAY_0;             //68h 
	uint32_t STEPCONFIG_1;            //6Ch 
	uint32_t STEPDELAY_1;             //70h
	uint32_t STEPCONFIG_2;            //74h
	uint32_t STEPDELAY_2;             //78h
	uint32_t STEPCONFIG_3;            //7Ch
	uint32_t STEPDELAY_3;             //80h 
	uint32_t STEPCONFIG_4;            //84h
	uint32_t STEPDELAY_4;             //88h
	uint32_t STEPCONFIG_5;            //8Ch
	uint32_t STEPDELAY_5;             //90h
	uint32_t STEPCONFIG_6;            //94h 
	uint32_t STEPDELAY_6;             //98h
	uint32_t STEPCONFIG_7;            //9Ch
	uint32_t STEPDELAY_7;             //A0h
	uint32_t STEPCONFIG_8;            //A4h
	uint32_t STEPDELAY_8;             //A8h 
	uint32_t STEPCONFIG_9;            //ACh
	uint32_t STEPDELAY_9;             //B0h
	uint32_t STEPCONFIG_10;           //B4h
	uint32_t STEPDELAY_10;            //B8h
	uint32_t STEPCONFIG_11;           //BCh 
	uint32_t STEPDELAY_11;            //C0h
	uint32_t STEPCONFIG_12;           //C4h
	uint32_t STEPDELAY_12;            //C8h
	uint32_t STEPCONFIG_13;           //CCh
	uint32_t STEPDELAY_13;            //D0h 
	uint32_t STEPCONFIG_14;           //D4h
	uint32_t STEPDELAY_14;            //D8h
	uint32_t STEPCONFIG_15;           //DCh
	uint32_t STEPDELAY_15;            //E0h
	uint32_t FIFOCOUNT_0;             //E4h 
	uint32_t FIFOTHR_0;               //E8h
	uint32_t DMAREQ_0;                //ECh
	uint32_t FIFOCOUNT_1;             //F0h
	uint32_t FIFOTHR_1;               //F4h
	uint32_t DMAREQ_1;                //F8h
	uint32_t RESERVED3[1];  		  //FCh
	uint32_t FIFO0DATA;               //100h
	uint32_t RESERVED4[63];  		  //104h
	uint32_t FIFO1DATA;               //200h
}ADC0_Typedef;


/*ADC1的寄存器偏移；参考芯片手册：P1849_1850*/
typedef struct {
	uint32_t REVISION;  		      //0h
	uint32_t RESERVED0[3];  		  //4h
	uint32_t SYSCONFIG;           	  //10h  
	uint32_t RESERVED1[4];  		  //14h      
	uint32_t IRQSTS_RAW;          	  //24h     
	uint32_t IRQSTS;              	  //28h       
	uint32_t IRQEN_SET;               //2Ch       
	uint32_t IRQEN_CLR;               //30h 
	uint32_t RESERVED2;  	    	  //34h       
	uint32_t DMAEN_SET;               //38h 
	uint32_t DMAEN_CLR;               //3Ch 
	uint32_t CTRL;                    //40h 
	uint32_t ADCSTAT;                 //44h 
	uint32_t ADCRANGE;                //48h 
	uint32_t CLKDIV;                  //4Ch  
	uint32_t RESERVED3;  	    	  //50h 	
	uint32_t STEPEN;                  //54h 
	uint32_t IDLECONFIG;              //58h 
	uint32_t SWIPE_COMPARE_REG1_2;    //5Ch 
	uint32_t SWIPE_COMPARE_REG3_4;    //60h 
	uint32_t STEPCONFIG1;             //64h  
	uint32_t STEPDELAY1;              //68h 
	uint32_t STEPCONFIG2;             //6Ch 
	uint32_t STEPDELAY2;              //70h 
	uint32_t STEPCONFIG3;             //74h 
	uint32_t STEPDELAY3;              //78h 
	uint32_t STEPCONFIG4;             //7Ch 
	uint32_t STEPDELAY4;              //80h 
	uint32_t STEPCONFIG5;             //84h 
	uint32_t STEPDELAY5;              //88h 
	uint32_t STEPCONFIG6;             //8Ch 
	uint32_t STEPDELAY6;              //90h 
	uint32_t STEPCONFIG7;             //94h 
	uint32_t STEPDELAY7;              //98h 
	uint32_t STEPCONFIG8;             //9Ch 
	uint32_t STEPDELAY8;              //A0h 
	uint32_t STEPCONFIG9;             //A4h 
	uint32_t STEPDELAY9;              //A8h 
	uint32_t STEPCONFIG10;            //ACh 
	uint32_t STEPDELAY10;             //B0h 
	uint32_t STEPCONFIG11;            //B4h 
	uint32_t STEPDELAY11;             //B8h 
	uint32_t STEPCONFIG12;            //BCh 
	uint32_t STEPDELAY12;             //C0h 
	uint32_t STEPCONFIG13;            //C4h 
	uint32_t STEPDELAY13;             //C8h 
	uint32_t STEPCONFIG14;            //CCh 
	uint32_t STEPDELAY14;             //D0h 
	uint32_t STEPCONFIG15;            //D4h 
	uint32_t STEPDELAY15;             //D8h 
	uint32_t STEPCONFIG16;            //DCh 
	uint32_t STEPDELAY16;             //E0h 
	uint32_t FIFO0COUNT;              //E4h 
	uint32_t FIFO0THR;                //E8h 
	uint32_t DMA0REQ;                 //ECh 
	uint32_t FIFO1COUNT;              //F0h 
	uint32_t FIFO1THR;                //F4h 
	uint32_t DMA1REQ;                 //F8h
	uint32_t RESERVED4;  		      //FCh
	uint32_t FIFO0DATA;               //100h 
	uint32_t RESERVED5[63];  		  //104h
	uint32_t FIFO1DATA;               //200h 
}ADC1_Typedef;

#define   ADC0  	    ((ADC0_Typedef *)ADC0_BASE)  
//ADC0_Typedef * ADC0 = ((ADC0_Typedef *) ADC0_BASE);
//(ADC0_Typedef *)ADC0_BASE->SYSCONFIG
#define   ADC0_DMA  	((ADC0_Typedef *)ADC0_DMA_BASE)  
#define   ADC1  	    ((ADC1_Typedef *)ADC1_BASE)  
#define   ADC1_DMA  	((ADC1_Typedef *)ADC1_DMA_BASE)

#endif
