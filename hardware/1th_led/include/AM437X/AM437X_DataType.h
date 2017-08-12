#ifndef _AM437X_DATATYPE_H_
#define _AM437X_DATATYPE_H_
//#include "AM437X_DataType.h"

typedef unsigned int  uint32_t;//或数据类型头文件；
typedef unsigned char uint16_t;//或数据类型头文件；

#define  	__REG32(x)					(*(volatile unsigned int *)(x))  
#define  	__REG16(x)					(*(volatile unsigned short int *)(x))  
#define  	__REG8(x)					(*(volatile unsigned char *)(x))  

#endif


