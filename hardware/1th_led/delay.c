/*********************************************************************************
   *Function:     delay
   *Description： 简单延时
   *Input:        循环次数
   *Output:       \
   *Return:       0
   *Others:       1500000约等于1s;
**********************************************************************************/
void  delay(unsigned int  i)
{
	volatile unsigned int count = i;
	while(count--);
}


/*********************************************************************************
   *Function:     delay_ms
   *Description： 精确延时
   *Input:        循环次数
   *Output:       \
   *Return:       0
   *Others:       
**********************************************************************************/
void  delay_ms(unsigned int  i)
{
	volatile unsigned int count = i;
	while(count--);
}

