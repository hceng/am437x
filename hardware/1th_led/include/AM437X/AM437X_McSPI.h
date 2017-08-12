#ifndef _AM437X_MCSPI_H_
#define _AM437X_MCSPI_H_

#include "AM437X_DataType.h"

/*I2C的寄存器偏移；参考芯片手册：P3264-3265*/
typedef struct {
	uint32_t HL_REV;              //00h
	uint32_t HL_HWINFO;           //04h
	uint32_t RESERVED0[2];        //08h
	uint32_t HL_SYSCONFIG;        //10h
	uint32_t RESERVED1[59];       //14h
	uint32_t REVISION;            //100h
	uint32_t RESERVED2[3];        //104h
	uint32_t SYSCONFIG;           //110h
	uint32_t SYSSTS;              //114h
	uint32_t IRQSTS;              //118h
	uint32_t IRQEN;               //11ch
	uint32_t WAKEUPEN;            //120h
	uint32_t SYST;                //124h
	uint32_t MODULCTRL;           //128h
	uint32_t CH0CONF;             //12ch
	uint32_t CH0STAT;             //130h
	uint32_t CH0CTRL;             //134h
	uint32_t TX0;                 //138h
	uint32_t RX0;                 //13ch
	uint32_t CH1CONF;             //140h
	uint32_t CH1STAT;             //144h
	uint32_t CH1CTRL;             //148h
	uint32_t TX1;                 //14ch
	uint32_t RX1;                 //150h
	uint32_t CH2CONF;             //154h
	uint32_t CH2STAT;             //158h
	uint32_t CH2CTRL;             //15ch
	uint32_t TX2;                 //160h
	uint32_t RX2;                 //164h
	uint32_t CH3CONF;             //168h
	uint32_t CH3STAT;             //16ch
	uint32_t CH3CTRL;             //170h
	uint32_t TX3;                 //174h
	uint32_t RX3;                 //178h
	uint32_t XFERLEVEL;           //17ch
	uint32_t DAFTX; 			  //180h
	uint32_t RESERVED3[7];        //184h
	uint32_t DAFRX;				  //1a0h
}McSPI_Typedef;

#define   McSPI0   		((McSPI_Typedef *)MCSPI0_BASE)  
#define   McSPI1   		((McSPI_Typedef *)MCSPI1_BASE)
#define   McSPI2   		((McSPI_Typedef *)MCSPI2_BASE)
#define   McSPI3   		((McSPI_Typedef *)MCSPI3_BASE)
#define   McSPI4   		((McSPI_Typedef *)MCSPI4_BASE)

#endif
