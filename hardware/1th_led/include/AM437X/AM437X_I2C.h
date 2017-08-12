#ifndef _AM437X_I2C_H_
#define _AM437X_I2C_H_

#include "AM437X_DataType.h"

/*I2C的寄存器偏移；参考芯片手册：P3264-3265*/
typedef struct {
	uint32_t REVNB_LO;           //00h   
	uint32_t REVNB_HI;           //04h 
	uint32_t RESERVED0[2];       //08h
	uint32_t SYSC;               //10h
	uint32_t RESERVED1[4];       //14h
	uint32_t IRQSTS_RAW;         //24h
	uint32_t IRQSTS;             //28h
	uint32_t IRQEN_SET;          //2ch
	uint32_t IRQEN_CLR;          //30h
	uint32_t WE;                 //34h
	uint32_t DMARXEN_SET;        //38h
	uint32_t DMATXEN_SET;        //3ch
	uint32_t DMARXEN_CLR;        //40h
	uint32_t DMATXEN_CLR;        //44h
	uint32_t DMARXWAKE_EN;       //48h
	uint32_t DMATXWAKE_EN;       //4ch 
	uint32_t RESERVED2[16];      //50h 
	uint32_t SYSS;               //90h
	uint32_t BUF;                //94h
	uint32_t CNT;                //98h
	uint32_t DATA;               //9ch
	uint32_t RESERVED3;          //a0h
	uint32_t CON;                //a4h
	uint32_t OA;                 //a8h
	uint32_t SA;                 //ach
	uint32_t PSC;                //b0h
	uint32_t SCLL;               //b4h
	uint32_t SCLH;               //b8h
	uint32_t SYSTEST;            //bch
	uint32_t BUFSTAT;            //c0h
	uint32_t OA1;                //c4h
	uint32_t OA2;                //c8h
	uint32_t OA3;                //cch
	uint32_t ACTOA;              //d0h
	uint32_t SBLOCK;             //d4h
}I2C_Typedef;

#define   I2C1   		((I2C_Typedef *)I2C1_BASE)  
#define   I2C2   		((I2C_Typedef *)I2C2_BASE)  

#endif
