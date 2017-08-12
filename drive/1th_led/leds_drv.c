#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/cdev.h>


#define TI_LEDS_CNT     4

int major;
static struct cdev leds_cdev;
static struct class *leds_cls;

static volatile unsigned long *PRCM_CM_PER_GPIO5_CLKCTRL = NULL;  
static volatile unsigned long *CTRL_CONF_UART3_RXD = NULL;  
static volatile unsigned long *CTRL_CONF_UART3_TXD = NULL;  
static volatile unsigned long *CTRL_CONF_UART3_CTSN = NULL;
static volatile unsigned long *CTRL_CONF_UART3_RTSN = NULL;
static volatile unsigned long *GPIO_OE = NULL;
static volatile unsigned long *GPIO_SETDATAOUT = NULL;
static volatile unsigned long *GPIO_DATAOUT = NULL; 

static int leds_drv_open(struct inode *inode, struct file *file)  
{    
	int minor = iminor(file->f_inode);

	printk(KERN_INFO"leds_drv_open!\n"); 

	*PRCM_CM_PER_GPIO5_CLKCTRL  = (0x01<<1);
	
    *CTRL_CONF_UART3_RXD  &= ~(0x7<<0 | 0x01<<16 | 0x01<<17 | 0x01<<18);
	*CTRL_CONF_UART3_RXD  |=  (0x7<<0 | 0x01<<17);

	*GPIO_OE              &= ~(0x01<<minor);
	*GPIO_SETDATAOUT      |=  (0x01<<minor);
	
    return 0;     
}   
  
static ssize_t leds_drv_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)  
{  
	int minor = iminor(file->f_inode);
	int val;  
	
	printk(KERN_INFO"leds_drv_write!\n");
	
	if (copy_from_user(&val, buf, count))
		return -EFAULT;
	
    if (val == 1)  *GPIO_DATAOUT |= (0x01<<minor);    
    else *GPIO_DATAOUT &= ~(0x01<<minor);
	
    return 0;  
}  

static struct file_operations leds_fops = {
    .owner  =   THIS_MODULE,  
    .open   =   leds_drv_open,     
	.write	=	leds_drv_write,	   
};

static int leds_drv_init(void)
{
	//1.申请设备号
	dev_t devid;

	printk(KERN_INFO"===leds_drv_init!===\n");
	
	if(alloc_chrdev_region(&devid, 0, TI_LEDS_CNT, "ti_leds") < 0)
    {
        printk("%s ERROR\n",__func__);
        goto error;
    }
	
    major = MAJOR(devid);

	//2.注册到系统中
	cdev_init(&leds_cdev, &leds_fops);        
    cdev_add(&leds_cdev, devid, TI_LEDS_CNT);   

    leds_cls = class_create(THIS_MODULE, "ti_leds");
	
    device_create(leds_cls, NULL, MKDEV(major, 0), NULL, "ti_led0"); 
    device_create(leds_cls, NULL, MKDEV(major, 1), NULL, "ti_led1"); 
    device_create(leds_cls, NULL, MKDEV(major, 2), NULL, "ti_led2"); 
    device_create(leds_cls, NULL, MKDEV(major, 3), NULL, "ti_led3");
	
	//3.硬件相关
	PRCM_CM_PER_GPIO5_CLKCTRL = ioremap(0x44DF8800+0x498, 0x04*1);

	CTRL_CONF_UART3_RXD       = ioremap(0x44E10000+0xA28, 0x04*4);
	CTRL_CONF_UART3_TXD       = CTRL_CONF_UART3_RXD + 1;
	CTRL_CONF_UART3_CTSN 	  = CTRL_CONF_UART3_RXD + 2;
	CTRL_CONF_UART3_RTSN	  = CTRL_CONF_UART3_RXD + 3; 
	 
	GPIO_OE                   = ioremap(0x48322000+0x134, 0x04); 
	GPIO_DATAOUT			  = ioremap(0x48322000+0x13C, 0x04);
	GPIO_SETDATAOUT           = ioremap(0x48322000+0x194, 0x04);
	
error:
    unregister_chrdev_region(MKDEV(major, 0), TI_LEDS_CNT);
	
	return 0;
}

static void leds_drv_exit(void)
{
	unsigned i;
	printk(KERN_INFO"leds_drv_exit!\n");
	
	for(i=0;i<TI_LEDS_CNT;i++)
	{
		device_destroy(leds_cls,  MKDEV(major, i));	
	}
	class_destroy(leds_cls);
	cdev_del(&leds_cdev);
	unregister_chrdev(major, "ti_leds"); 
	
	iounmap(PRCM_CM_PER_GPIO5_CLKCTRL);
	iounmap(CTRL_CONF_UART3_RXD);
	iounmap(GPIO_OE);
	iounmap(GPIO_DATAOUT);
	iounmap(GPIO_SETDATAOUT);
}

module_init(leds_drv_init);
module_exit(leds_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board leds drvice");
MODULE_ALIAS("character device:ti_leds");
MODULE_VERSION("V1.0");
