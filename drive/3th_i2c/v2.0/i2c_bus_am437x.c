#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/cpufreq.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <asm/irq.h>

struct am437x_i2c_xfer_data {
    struct i2c_msg *msgs;
    uint32_t cur_rec;
    uint32_t cur_send;
    uint32_t reg_cnt;
    uint32_t err;
    wait_queue_head_t wait;
};
static struct am437x_i2c_xfer_data i2c_data;

static volatile unsigned long *CTRL_CONF_I2C0_SDA;
static volatile unsigned long *CTRL_CONF_I2C0_SCL;
static volatile unsigned long *PRCM_CM_WKUP_I2C0_CLKCTRL;
static volatile unsigned long *PRCM_CM_WKUP_CLKSTCTRL;
static volatile unsigned long *PRCM_CM_PER_L4LS_CLKSTCTRL;

struct am437x_i2c_regs {
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
};

static  volatile struct am437x_i2c_regs *I2C0;


static void am437x_i2c_start(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 
    
    I2C0->IRQSTS	|=  0x7FFF;
    I2C0->IRQEN_CLR |=  0x7FFF;

    if(i2c_data.msgs->flags & I2C_M_RD) //read
    {

        I2C0->CON |=  (0x01<<10 | (0x01<<15));  //MST=1  TRX=0 
        I2C0->CON &= ~(0x01<<9);

        I2C0->IRQEN_SET |= (0x01<<3);
    }
    else//write
    {
        I2C0->CON |= (0x01<<9 | 0x01<<10 | 0x01<<15); //MST=1  TRX=1    

        I2C0->IRQEN_SET |= (0x01<<4);
    }
    
    I2C0->CON |= (0x01<<0);
}


static void am437x_i2c_stop(int err)
{
    printk(KERN_INFO"%s OK.\n",__func__); 

    i2c_data.err = err;

    mdelay(2);//为了防止读EEPROM的时候，写操作后，马上就读操作，导致错误;
    I2C0->CON |= (0x01<<1); //stop
    ndelay(50);

    /*唤醒*/
    wake_up(&i2c_data.wait);
}

static irqreturn_t i2c_xfer_irq(int irq, void *dev_id)
{
    unsigned int status = 0;

    printk(KERN_INFO"%s OK.\n",__func__); 

    status = I2C0->IRQSTS;

    //I2C0->IRQSTS = (status & (0x01<<1 |0x01<<3 | 0x01<<4));
    I2C0->IRQSTS = (status & (0x01<<3 | 0x01<<4));

    if(status & (0x01<<3))//receive
    {
        //printk(KERN_INFO"i2c receive.\n"); 
        I2C0->IRQSTS |= (0x01<<3);

        i2c_data.msgs->buf[i2c_data.cur_rec] = I2C0->DATA;
        i2c_data.cur_rec++;

        if(i2c_data.cur_rec == i2c_data.reg_cnt) 
        {
            I2C0->IRQEN_CLR |= (0x01<<3); 
            am437x_i2c_stop(1);
        }

    }
    if (status & (0x01<<4))//send
    {
        //printk(KERN_INFO"i2c send.\n");

        I2C0->IRQSTS |= (0x01<<4);	

        I2C0->DATA = i2c_data.msgs->buf[i2c_data.cur_send];
        i2c_data.cur_send++;

        if(i2c_data.cur_send == i2c_data.reg_cnt)
        {
            I2C0->IRQEN_CLR |= (0x01<<4);
            am437x_i2c_stop(1);
        }
    } 
    
    //判断是否有ack和bus空闲

    I2C0->IRQSTS	|=  0x7FFF;

    return IRQ_HANDLED;
}


static int  am437x_i2c_xfer(struct i2c_adapter *adap,
        struct i2c_msg *msgs, int num)
{
    //用于实现I2C协议，将i2c_msg消息传给i2c设备
    unsigned long timeout;

    printk(KERN_INFO"%s OK.\n",__func__); 

    //把num个i2c_msg的I2C数据发送出去/读进来
    i2c_data.msgs    = msgs;
    i2c_data.cur_rec = 0;
    i2c_data.cur_send = 0;
    i2c_data.err     = -ENODEV;

    I2C0->CNT = i2c_data.msgs->len;
    i2c_data.reg_cnt = I2C0->CNT;

    I2C0->SA = i2c_data.msgs->addr;
    
    am437x_i2c_start();

    /*休眠*/
    if(i2c_data.msgs->flags & I2C_M_RD) //读
    {
        timeout = wait_event_timeout(i2c_data.wait,(i2c_data.cur_rec == i2c_data.reg_cnt), HZ * 5);//5S         
    }
    else
    {
        timeout = wait_event_timeout(i2c_data.wait, (i2c_data.cur_send == i2c_data.reg_cnt), HZ * 5);//5S
    }

    if(0 == timeout)
    {
        printk("am437x i2c timeout.\n");
        return -ETIMEDOUT;
    }
    else
    {
        return i2c_data.err;
    }
}

static u32  am437x_i2c_func(struct i2c_adapter *adap)
{
    printk(KERN_INFO"%s OK.\n",__func__); 
    //用于返回总线支持的协议
    return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
}

static const struct i2c_algorithm am437x_i2c_algo = {
    //	.smbus_xfer     = ,
    .master_xfer	= am437x_i2c_xfer,
    .functionality	= am437x_i2c_func,
};

static struct i2c_adapter am437x_i2c_adapter = {
    .name	        = "i2c_adapter",
    .algo		    = &am437x_i2c_algo,//i2c总线通信方法
    .owner 		    = THIS_MODULE,
};
                                                              
static void i2c_init(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 

    /*clk*/
    PRCM_CM_WKUP_I2C0_CLKCTRL   = ioremap(0x44DF2800+0x340, 0x04*1);
    *PRCM_CM_WKUP_I2C0_CLKCTRL  |= (0x02<<0);

    PRCM_CM_WKUP_CLKSTCTRL      = ioremap(0x44DF2800+0x300, 0x04*1);
    *PRCM_CM_WKUP_CLKSTCTRL     |= (0x01<<14);

    PRCM_CM_PER_L4LS_CLKSTCTRL  = ioremap(0x44DF8800+0x400, 0x04*1);
    *PRCM_CM_PER_L4LS_CLKSTCTRL |= (0x01<<27);

    /*GPIO:gpio3_5->I2C0_SDA;gpio3_6->I2C0_SCL*/

    CTRL_CONF_I2C0_SDA = ioremap(0x44E10000+0x0988, 0x04*1);
    CTRL_CONF_I2C0_SCL = ioremap(0x44E10000+0x098C, 0x04*1);

    *CTRL_CONF_I2C0_SDA &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);
    *CTRL_CONF_I2C0_SCL &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);

    /*I2C0 set*/
    I2C0 = ioremap(0x44E0B000, sizeof(struct am437x_i2c_regs));

    I2C0->CON  &= ~(0x01<<15);//reset

    I2C0->SYSC &= ~(0x01<<0);//Auto Idle disabled.

    I2C0->PSC  = 3;//the module divided by (PSC + 1) -> 48M/(3+1)=12M

    I2C0->SCLL = 63;//tLOW = (SCLL + 7) * ICLK time period
    I2C0->SCLH = 65;//tHIGH = (SCLH + 5) * ICLK time period

    //I2C0->SA = 0x50;//Slave address.x 1010 000

    I2C0->CON  |=  (0x01<<15);//Module enabled	
}

static int i2c_bus_drv_init(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 

    //硬件相关的设置
    i2c_init();

    if (request_irq(102, i2c_xfer_irq, 0, "am437x-i2c", NULL))
        return -EAGAIN;

    init_waitqueue_head(&i2c_data.wait);

    i2c_add_adapter(&am437x_i2c_adapter);//会在/sys/class/i2c-adapter下生成i2c-x

    return 0;
}

static void i2c_bus_drv_exit(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 

    iounmap(CTRL_CONF_I2C0_SDA);
    iounmap(CTRL_CONF_I2C0_SCL);

    iounmap(PRCM_CM_WKUP_I2C0_CLKCTRL);
    iounmap(PRCM_CM_WKUP_CLKSTCTRL);
    iounmap(PRCM_CM_PER_L4LS_CLKSTCTRL);

    iounmap(I2C0);

    free_irq(102, NULL);

    i2c_del_adapter(&am437x_i2c_adapter);
}


module_init(i2c_bus_drv_init);
module_exit(i2c_bus_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board i2c bus drvice.");
MODULE_ALIAS("ti_i2c");
MODULE_VERSION("V2.0");