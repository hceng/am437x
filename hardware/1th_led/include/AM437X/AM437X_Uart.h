
#ifndef  __AM437X_UART_H__
#define   __AM437X_UART_H__
//#include  "AM437X_Uart.h"

#include "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

//
/*
下面的方法不知道行不行
后面用enum枚举，来解决多个寄存器占用相同的地址
enum  {
THR  =0 ;
RHR  =0 ;
}

定义uart结构体
#define    UART0_THR 				   (*(volatile unsigned int *)(UART0_BASE+0x00)) 	

变为UART0->THR
*/
#define    UART0_THR 			    (*(volatile unsigned int *)(UART0_BASE+0x00)) 	
#define    UART0_RHR 			    (*(volatile unsigned int *)(UART0_BASE+0x00)) 	
#define    UART0_DLL 			    (*(volatile unsigned int *)(UART0_BASE+0x00)) 	
#define    UART0_IER_IRDA 		    (*(volatile unsigned int *)(UART0_BASE+0x04)) 	
#define    UART0_IER_CIR 		    (*(volatile unsigned int *)(UART0_BASE+0x04)) 	
#define    UART0_IER 			    (*(volatile unsigned int *)(UART0_BASE+0x04)) 	
#define    UART0_DLH		        (*(volatile unsigned int *)(UART0_BASE+0x04)) 	
#define    UART0_EFR 			    (*(volatile unsigned int *)(UART0_BASE+0x08)) 	
#define    UART0_IIR 			    (*(volatile unsigned int *)(UART0_BASE+0x08)) 	
#define    UART0_IIR_CIR 		    (*(volatile unsigned int *)(UART0_BASE+0x08)) 	
#define    UART0_FCR  		        (*(volatile unsigned int *)(UART0_BASE+0x08)) 	
#define    UART0_LCR    		    (*(volatile unsigned int *)(UART0_BASE+0x0C)) 	
#define    UART0_MCR 			    (*(volatile unsigned int *)(UART0_BASE+0x10)) 	
#define    UART0_XON1_ADDR1         (*(volatile unsigned int *)(UART0_BASE+0x10)) 	
#define    UART0_XON2_ADDR2         (*(volatile unsigned int *)(UART0_BASE+0x14)) 	
#define    UART0_LSR_CIR 		    (*(volatile unsigned int *)(UART0_BASE+0x14)) 	
#define    UART0_LSR_IRDA 	   	    (*(volatile unsigned int *)(UART0_BASE+0x14)) 	
#define    UART0_LSR   	   	        (*(volatile unsigned int *)(UART0_BASE+0x14)) 	
#define    UART0_TCR 			    (*(volatile unsigned int *)(UART0_BASE+0x18)) 	
#define    UART0_MSR 			    (*(volatile unsigned int *)(UART0_BASE+0x18)) 	
#define    UART0_XOFF1 		        (*(volatile unsigned int *)(UART0_BASE+0x18)) 	
#define    UART0_SPR 			    (*(volatile unsigned int *)(UART0_BASE+0x1C)) 	
#define    UART0_TLR 			    (*(volatile unsigned int *)(UART0_BASE+0x1C)) 	
#define    UART0_XOFF2 		        (*(volatile unsigned int *)(UART0_BASE+0x1C)) 	
#define    UART0_MDR1 			    (*(volatile unsigned int *)(UART0_BASE+0x20)) 	
#define    UART0_MDR2 			    (*(volatile unsigned int *)(UART0_BASE+0x24)) 	
#define    UART0_TXFLL 		        (*(volatile unsigned int *)(UART0_BASE+0x28)) 	
#define    UART0_SFLSR 		        (*(volatile unsigned int *)(UART0_BASE+0x28)) 	
#define    UART0_RESUME 		    (*(volatile unsigned int *)(UART0_BASE+0x2C)) 	
#define    UART0_TXFLH 		   		(*(volatile unsigned int *)(UART0_BASE+0x2C)) 	
#define    UART0_RXFLL 		   		(*(volatile unsigned int *)(UART0_BASE+0x30)) 	
#define    UART0_SFREGL		  		(*(volatile unsigned int *)(UART0_BASE+0x30)) 	
#define    UART0_SFREGH 		    (*(volatile unsigned int *)(UART0_BASE+0x34)) 	
#define    UART0_RXFLH 		  		(*(volatile unsigned int *)(UART0_BASE+0x34)) 	
#define    UART0_BLR   		   		(*(volatile unsigned int *)(UART0_BASE+0x38)) 	
#define    UART0_UASR 			    (*(volatile unsigned int *)(UART0_BASE+0x38)) 	
#define    UART0_ACREG 		   		(*(volatile unsigned int *)(UART0_BASE+0x3C)) 	
#define    UART0_SCR 			    (*(volatile unsigned int *)(UART0_BASE+0x40)) 	
#define    UART0_SSR 			    (*(volatile unsigned int *)(UART0_BASE+0x44)) 	
#define    UART0_EBLR 			    (*(volatile unsigned int *)(UART0_BASE+0x48)) 	
#define    UART0_MVR 			    (*(volatile unsigned int *)(UART0_BASE+0x50)) 	
#define    UART0_SYSC 			    (*(volatile unsigned int *)(UART0_BASE+0x54)) 	
#define    UART0_SYSS 			    (*(volatile unsigned int *)(UART0_BASE+0x58)) 	
#define    UART0_WER 			  	(*(volatile unsigned int *)(UART0_BASE+0x5C)) 	
#define    UART0_CFPS 			  	(*(volatile unsigned int *)(UART0_BASE+0x60)) 	
#define    UART0_RXFIFO_LVL      	(*(volatile unsigned int *)(UART0_BASE+0x64)) 	
#define    UART0_TXFIFO_LVL      	(*(volatile unsigned int *)(UART0_BASE+0x68)) 	
#define    UART0_IER2 			    (*(volatile unsigned int *)(UART0_BASE+0x6C)) 	
#define    UART0_ISR2 			    (*(volatile unsigned int *)(UART0_BASE+0x70)) 	
#define    UART0_FREQ_SEL 	        (*(volatile unsigned int *)(UART0_BASE+0x74)) 	
#define    UART0_MDR3 			    (*(volatile unsigned int *)(UART0_BASE+0x80)) 	
#define    UART0_TX_DMA_THR         (*(volatile unsigned int *)(UART0_BASE+0x84)) 	
                                                       
                                                       
                                                       
#endif                                                                                                        
                                                       