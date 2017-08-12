#include "AM437X/AM437X_SOC.h"

void  uart0_clock_enable()
{
	volatile unsigned  int  temp=0;
	
	PRCM_CM_WKUP_UART0_CLKCTRL |=  (0x2);

	do
	{
		temp =  PRCM_CM_WKUP_CLKSTCTRL;
	}
	while((0x1<<15) !=  (temp  &  (0x1<<15) ));
		
	do
	{
		temp =  PRCM_CM_WKUP_UART0_CLKCTRL;
	}
	while((0x0<<16) !=  (temp  &  (0x3<<16) ));
	
}


void  uart0_iomux()
{
	//unsigned  int  temp=0;

CTRL_CONF_UART0_TXD = ((0<<18) |(1<<16) | (0<<0) );
CTRL_CONF_UART0_RXD =  ((1<<18) |(1<<16) | (0<<0) );

}


void  uart0_config()
{	
	unsigned  int  temp=0;
	//unsigned  int  enhanced_en_val=0;
		

	UART0_SYSC |= (1<<1);
	do
	{
		temp =  UART0_SYSS;
	}
	while( !(temp & (0x1)) );


	UART0_LCR   = 0x0;	
	UART0_FCR   = 0X0;
	
	UART0_MDR1 |= (0x7);
	UART0_LCR   = 0x00bf;


	UART0_EFR  |= (0x1<<4);
	UART0_LCR   = 0x0;	
	
	UART0_IER  &=~(1<<4);


	UART0_LCR   = 0x00bf;


	UART0_DLH = ( 0 & 0X3F);
	UART0_DLL = (26 & 0XFF);	


	UART0_EFR  &= ~(0x1<<4);

	UART0_LCR  = (3<<0);
	
	UART0_MDR1 &= ~(0x7);
	
}


void  uart_init()
{
	uart0_clock_enable();

	uart0_iomux();

	uart0_config();

}


void  uart_PutChar(char  c)
{
	while( (1<<6) !=( UART0_LSR & (1<<6) ));
	
	UART0_THR = (c & 0XFF);	
	
}


void uart_PutString(char *ptr)
{
	 
	while(*ptr != '\0')
	{          
		uart_PutChar(*ptr++);
	}
	uart_PutChar('\r');//secureCRTÊÇ\r\n»»ÐÐ
	uart_PutChar('\n');
}

