/*************************************************************************
    > File Name: main.c
    > Author: hceng
    > Description: 完善AM437X裸机LED
    > Created Time: 20170726
*************************************************************************/

#include "AM437X/AM437X_SOC.h"
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "printf.h"

int  loop_judge_register_bits(unsigned  int reg_addr, unsigned  int bits, unsigned  int expected_val);
void debug_led(char *str);
void led_test(void);

int  main()
{
	uart_init();
	_100ask_printf("uart_init ok!\r\n");

	while(1)
	{
		led_test();
	}
	
	return 0;
}


/*********************************************************************************
   *Function:     loop_judge_register_bits
   *Description： 循环判断某个寄存器的值为多少
   *Input:        寄存器地址，哪些bit位，期待值
   *Output:       \
   *Return:       0
   *Others:       \
**********************************************************************************/
int  loop_judge_register_bits(unsigned  int reg_addr, unsigned  int bits, unsigned  int expected_val)
{
	volatile unsigned  int  reg=reg_addr;	
	unsigned  int  tmp=0;//volatile unsigned  int  tmp=0;
	
	do
	{
		tmp = reg;
		tmp = tmp & (bits); 
	}
	while(expected_val !=  tmp);//判断

	return 0;
}



/*********************************************************************************
   *Function:     debug_adc
   *Description： 调试程序打印出全部相关寄存器
   *Input:        字符串标记
   *Output:       \
   *Return:       0
   *Others:       将传入参数由整型改为字符型
**********************************************************************************/
void debug_adc(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
	//_100ask_printf("FIFO1DATA		 = 0x%x\r\n",ADC0->FIFO1DATA		 );  
	_100ask_printf("******************************************************\r\n");


}


void led_test(void)
{
	led_init();
	
	led_on();
	delay(1500000);
	led_off();
	delay(1500000);
	led_on();
	delay(1500000);
	led_off();
	delay(1500000);
	
	led1_on();
	delay(1500000);
	led1_off();
	delay(1500000);
	led2_on();
	delay(1500000);
	led2_off();
	delay(1500000);	
	led3_on();
	delay(1500000);
	led3_off();
	delay(1500000);	
	led4_on();
	delay(1500000);
	led4_off();
	delay(1500000);

}

