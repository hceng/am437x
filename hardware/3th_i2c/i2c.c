#include "AM437X/AM437X_SOC.h"
#include "i2c.h"
#include "uart.h"
#include "printf.h"
#include "int.h" 
#include "delay.h" 

#ifdef GPIO_I2C

static void i2c_delay(volatile int time)
{
    time = time*1;
    for (; time > 0; time--);
}

static void SDA(char x)
{
	GPIO3->OE &= ~(0x01<<5);
		
    if(x) {
		GPIO3->DATAOUT |=  (0x01<<5);
    } 
    else {
		GPIO3->DATAOUT &= ~(0x01<<5);
    }     
}

static void SCL(char x)
{
	GPIO3->OE &= ~(0x01<<6);

    if(x) {
        GPIO3->DATAOUT |=  (0x01<<6);
    } 
    else {
		GPIO3->DATAOUT &= ~(0x01<<6);
    }     
}

static char GET_SDA(void)
{
	GPIO3->OE |= (0x01<<5);
	
    return (GPIO3->DATAIN & (0x01<<5)?1:0);
}


void i2c_init(void)
{

    PRCM_CM_PER_GPIO3_CLKCTRL  |= (0x02<<0);

    //gpio3_5->I2C0_SDA;gpio3_6->I2C0_SCL;gpio3_7->WP
	//CTRL_CONF_I2C0_SDA ;//GPIO模式I2C，默认配置即可
	//CTRL_CONF_I2C0_SCL ;//GPIO模式I2C，默认配置即可

	GPIO3->OE      &= ~(0x01<<7 | 0x01<<6 | 0x01<<5);//输出
	GPIO3->DATAOUT |=  (0x01<<7 | 0x01<<6 | 0x01<<5);//拉高
}

static void i2c_start(void)
{
    SCL(1);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);
    SDA(0);
    i2c_delay(1);
    
    SCL(0); 
    i2c_delay(1);
}

static void i2c_stop(void)
{
    SDA(0);
    i2c_delay(1);
    
    SCL(1);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);
}

static int i2c_ack(void)
{
    int pin_val;
      
    SCL(0);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);

    //实测中，am437x引脚由输出设置为输入的时候，会有一个高电平
    //因此，趁现在SCL为低，先设置为输入
	GET_SDA();
	
    SCL(1);
    i2c_delay(1);
    
    pin_val = GET_SDA();
    i2c_delay(1);
    
    SCL(0);
    i2c_delay(1);
   
    return pin_val;
}


static void i2c_write(unsigned char data)
{
    int i = 0;
    
    for(i=0; i<8; i++) {
        SCL(0);
        i2c_delay(1);
        
        if(data & 0x80) SDA(1);
        else SDA(0);
        data = data<<1; 
        i2c_delay(1);
        
        SCL(1);
        i2c_delay(1);
    }
    SCL(0);
    i2c_delay(1);
}

static unsigned char i2c_read(void)
{
    int i = 0;
    unsigned char data = 0;
    
    SCL(0);
    i2c_delay(1);
    SDA(1);
   
    GET_SDA();//同理
	i2c_delay(1);
	
    for(i=0; i<8; i++) {
        SCL(1);
        i2c_delay(1);
        
        data = data<<1;
        if(GET_SDA()) data |= 0x01;
  
        SCL(0);
        i2c_delay(1);
    }
    
    SCL(1);//再给eeprom的ack提供一个时钟周期
    i2c_delay(1);
    SCL(0);
    i2c_delay(1);
    
    return data;
}

static void eeprom_write_protect(char x)
{
	if(x)
		GPIO3->DATAOUT |=  (0x01<<7);
	else 
		GPIO3->DATAOUT &= ~(0x01<<7);
}

void eeprom_write(unsigned char addr, unsigned char data)
{
   eeprom_write_protect(0);

   i2c_start();
   
   i2c_write(0xA0);
   while(i2c_ack());
   
   i2c_write(addr>>8);
   while(i2c_ack());
   i2c_write(addr);
   while(i2c_ack());

   i2c_write(data);
   while(i2c_ack());
   
   i2c_stop();

   eeprom_write_protect(1);
}

unsigned char eeprom_read(unsigned char addr)
{
    unsigned char data = 0;
	
    eeprom_write_protect(0);
	
    i2c_start();
    
    i2c_write(0xA0);
    while(i2c_ack());
  
	i2c_write(addr>>8);
	while(i2c_ack());
	i2c_write(addr);
	while(i2c_ack());

    i2c_stop();
    
    i2c_delay(10);
    
    i2c_start();
    
    i2c_write(0xA1);
   	while(i2c_ack());

    data = i2c_read();
    
    i2c_stop();
	
	eeprom_write_protect(1);

	return data;
}

#endif


#ifdef REG_I2C

void i2c0_irq(void)
{
	unsigned int status = 0;

	status = I2C0->IRQSTS;
	I2C0->IRQSTS = (status & (0x01<<3 | 0x01<<4));

	if(status & (0x01<<3))//receive
    {
		I2C0->IRQSTS |= (0x01<<3);

		 if(r_count == num)
         {	
              I2C0->IRQEN_CLR |= (0x01<<3);
              I2C0->CON |= (0x01<<1);//stop  
         } 	 
		 else
		 {
     		  data_from_slave[r_count++] = (unsigned char)I2C0->DATA;
		 }
	}

	if (status & (0x01<<4))//send
    {

        I2C0->DATA = data_to_slave[t_count++];

		I2C0->IRQSTS |= (0x01<<4);		 
						
         if(t_count == num)
         {
              I2C0->IRQEN_CLR |= (0x01<<4);
         }
    }
}

void eeprom_write_protect(char x)
{
	if(x)
		GPIO3->DATAOUT |=  (0x01<<7);
	else 
		GPIO3->DATAOUT &= ~(0x01<<7);
}

static unsigned int i2c_master_bus_busy(void)
{
	if(I2C0->IRQSTS_RAW & (0x01<<12))	
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char eeprom_read(unsigned char addr)
{
	unsigned char data = 0;
	
	eeprom_write_protect(0);

    data_to_slave[0] = addr>>8;
    data_to_slave[1] = (addr & 0xFF);

    t_count = 0;
    r_count = 0;

    I2C0->CNT = 0x02;

	num = I2C0->CNT;

	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x6FFF;

	I2C0->CON |= (0x01<<9 | 0x01<<10 | 0x01<<15); //MST=1  TRX=1  

	I2C0->IRQEN_SET |= (0x01<<4);
	
	I2C0->CON |= (0x01<<0);

	while(i2c_master_bus_busy() == 0);
	
	while(t_count != num);
	while(!(I2C0->IRQSTS_RAW & (0x01<<2)));

//----------------------------------------------------------------//

	I2C0->CNT = 0x01;

	num = I2C0->CNT;
	
	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x6FFF;

	I2C0->CON |=  (0x01<<10 | (0x01<<15));	
	I2C0->CON &= ~(0x01<<9);
	
	I2C0->IRQEN_SET |= (0x01<<3 | 0x01<<8);

	I2C0->CON |= (0x01<<0);

	while(i2c_master_bus_busy() == 0);

	while(r_count != num);

	data = data_from_slave[0];

	eeprom_write_protect(1);

	return data;
}


void eeprom_write(unsigned char addr, unsigned char data)
{	
	eeprom_write_protect(0);

    data_to_slave[0] = addr>>8;
    data_to_slave[1] = (addr & 0xFF);
	data_to_slave[2] = data;

    t_count = 0;

    I2C0->CNT = 0x03;
	num = I2C0->CNT;

	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x7FFF;

	I2C0->CON |= (0x01<<9 | 0x01<<10 | 0x01<<15); //MST=1  TRX=1  
	
	I2C0->IRQEN_SET |= (0x01<<4);
	
	I2C0->CON |= (0x01<<0);
    
	while(i2c_master_bus_busy() == 0);

	while(t_count != num);
	
	I2C0->CON |= (0x01<<1); //stop

	eeprom_write_protect(1);
}


static void i2c_gpio_init(void)
{
	PRCM_CM_WKUP_I2C0_CLKCTRL |= (0x02<<0); 
	PRCM_CM_WKUP_CLKSTCTRL    |= (0x01<<14);
	PRCM_CM_PER_L4LS_CLKSTCTRL|= (0x01<<27);

	PRCM_CM_PER_GPIO3_CLKCTRL  |= (0x02<<0);
	
	//gpio3_5->I2C0_SDA;gpio3_6->I2C0_SCL;gpio3_7->WP

	CTRL_CONF_I2C0_SDA &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);
	CTRL_CONF_I2C0_SCL &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);
    //CTRL_CONF_EMU0
	GPIO3->OE      &= ~(0x01<<7);
	GPIO3->DATAOUT |=  (0x01<<7);
}


void i2c_init(void)
{
	i2c_gpio_init();

	register_irq(IRQ_I2C0, i2c0_irq);
	
	interrupt_init(IRQ_I2C0);

	I2C0->CON  &= ~(0x01<<15);//reset

	I2C0->SYSC &= ~(0x01<<0);//Auto Idle disabled.

	I2C0->PSC  = 3;//the module divided by (PSC + 1) -> 48M/(3+1)=12M

	I2C0->SCLL = 63;//tLOW = (SCLL + 7) * ICLK time period
	I2C0->SCLH = 65;//tHIGH = (SCLH + 5) * ICLK time period

	I2C0->SA = 0x50;//Slave address.1010 000

	I2C0->CON  |=  (0x01<<15);//Module enabled	
}



void debug_i2c(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
    
	_100ask_printf("I2C0->REVNB_HI    = 0x%x\r\n",I2C0->REVNB_HI    );
	_100ask_printf("I2C0->REVNB_LO    = 0x%x\r\n",I2C0->REVNB_LO    );
	_100ask_printf("I2C0->REVNB_HI    = 0x%x\r\n",I2C0->REVNB_HI    );
	_100ask_printf("I2C0->SYSC        = 0x%x\r\n",I2C0->SYSC        );
	_100ask_printf("I2C0->IRQSTS_RAW  = 0x%x\r\n",I2C0->IRQSTS_RAW  );
	_100ask_printf("I2C0->IRQSTS      = 0x%x\r\n",I2C0->IRQSTS      );
	_100ask_printf("I2C0->IRQEN_SET   = 0x%x\r\n",I2C0->IRQEN_SET   );
	_100ask_printf("I2C0->IRQEN_CLR   = 0x%x\r\n",I2C0->IRQEN_CLR   );
	_100ask_printf("I2C0->WE          = 0x%x\r\n",I2C0->WE          );
	_100ask_printf("I2C0->DMARXEN_SET = 0x%x\r\n",I2C0->DMARXEN_SET );
	_100ask_printf("I2C0->DMATXEN_SET = 0x%x\r\n",I2C0->DMATXEN_SET );
	_100ask_printf("I2C0->DMARXEN_CLR = 0x%x\r\n",I2C0->DMARXEN_CLR );
	_100ask_printf("I2C0->DMATXEN_CLR = 0x%x\r\n",I2C0->DMATXEN_CLR );
	_100ask_printf("I2C0->DMARXWAKE_EN= 0x%x\r\n",I2C0->DMARXWAKE_EN);
	_100ask_printf("I2C0->DMATXWAKE_EN= 0x%x\r\n",I2C0->DMATXWAKE_EN);
	_100ask_printf("I2C0->SYSS        = 0x%x\r\n",I2C0->SYSS        );
	_100ask_printf("I2C0->BUF         = 0x%x\r\n",I2C0->BUF         );
	_100ask_printf("I2C0->CNT         = 0x%x\r\n",I2C0->CNT         );
	_100ask_printf("I2C0->DATA        = 0x%x\r\n",I2C0->DATA        );
	_100ask_printf("I2C0->CON         = 0x%x\r\n",I2C0->CON         );
	_100ask_printf("I2C0->OA          = 0x%x\r\n",I2C0->OA          );
	_100ask_printf("I2C0->SA          = 0x%x\r\n",I2C0->SA          );
	_100ask_printf("I2C0->PSC         = 0x%x\r\n",I2C0->PSC         );
	_100ask_printf("I2C0->SCLL        = 0x%x\r\n",I2C0->SCLL        );
	_100ask_printf("I2C0->SCLH        = 0x%x\r\n",I2C0->SCLH        );
	_100ask_printf("I2C0->SYSTEST     = 0x%x\r\n",I2C0->SYSTEST     );
	_100ask_printf("I2C0->BUFSTAT     = 0x%x\r\n",I2C0->BUFSTAT     );
	_100ask_printf("I2C0->OA1         = 0x%x\r\n",I2C0->OA1         );
	_100ask_printf("I2C0->OA2         = 0x%x\r\n",I2C0->OA2         );
	_100ask_printf("I2C0->OA3         = 0x%x\r\n",I2C0->OA3         );
	_100ask_printf("I2C0->ACTOA       = 0x%x\r\n",I2C0->ACTOA       );
	_100ask_printf("I2C0->SBLOCK      = 0x%x\r\n",I2C0->SBLOCK      ); 

	_100ask_printf("******************************************************\r\n");
}


#endif

