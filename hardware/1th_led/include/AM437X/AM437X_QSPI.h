#ifndef _AM437X_QSPI_H_
#define _AM437X_QSPI_H_
#include "AM437X_DataType.h"

/*I2C的寄存器偏移；参考芯片手册：P3679*/
typedef struct {
	uint32_t PID;                 //00h  
	uint32_t RESERVED0[3];  	  //04h 
	uint32_t SYSCONFIG;           //10h
	uint32_t RESERVED1[3];        //14h
	uint32_t INTR_STS_RAW_SET;    //20h
	uint32_t INTR_STS_EN_CLR;     //24h
	uint32_t INTR_EN_SET_REG;     //28h
	uint32_t INTR_EN_CLR_REG;     //2ch
	uint32_t INTC_EOI_REG;        //30h
	uint32_t RESERVED2[3];        //34h
	uint32_t CLOCK_CNTRL_REG;     //40h
	uint32_t DC_REG;              //44h
	uint32_t CMD_REG;             //48h
	uint32_t STS_REG;             //4ch
	uint32_t DATA_REG;            //50h
	uint32_t SETUP_REG_0;         //54h
	uint32_t SETUP_REG_1;         //58h
	uint32_t SETUP_REG_2;         //5ch
	uint32_t SETUP_REG_3;         //60h
	uint32_t SWITCH_REG;          //64h
	uint32_t DATA_REG_1;          //68h
	uint32_t DATA_REG_2;          //6ch
	uint32_t DATA_REG_3;          //70h
}QSPI_Typedef;

#define   QSPI1   		((QSPI_Typedef *)QSPI1_BASE)  
#define   QSPI2   		((QSPI_Typedef *)QSPI2_BASE)  

#endif
