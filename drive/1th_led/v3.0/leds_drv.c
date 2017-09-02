#include <linux/module.h>  
#include <linux/version.h>  
#include <linux/init.h>  
#include <linux/fs.h>  
#include <linux/interrupt.h>  
#include <linux/irq.h>  
#include <linux/sched.h>  
#include <linux/pm.h>  
#include <linux/sysctl.h>  
#include <linux/proc_fs.h>  
#include <linux/delay.h>  
#include <linux/platform_device.h>  
#include <linux/input.h>  
#include <linux/irq.h>  
#include <asm/uaccess.h>  
#include <asm/io.h> 
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>


#define TI_LEDS_CNT     4

int major;
static struct cdev leds_cdev;
static struct class *leds_cls;
static int led0,led1,led2,led3; 

static int leds_drv_open(struct inode *inode, struct file *file)  
{    
    printk(KERN_INFO"%s OK.\n",__func__); 

    return 0;     
}   
  
static ssize_t leds_drv_write(struct file *file, const char __user *user_buf, size_t count, loff_t * ppos)  
{  
    int minor = iminor(file->f_inode); 
	char buf;
	
    printk(KERN_INFO"%s OK.\n",__func__);

    if(count != 1){
        printk(KERN_INFO"write count != 1.\n"); 
        return 1;
    }

    if (copy_from_user(&buf, user_buf, count))
        return -EFAULT;
	
    if(0x01 == buf)
    {
        switch(minor){
        case 0:
            gpio_set_value(led0, 0);
            break;
        case 1:
            gpio_set_value(led1, 0);
            break;
        case 2:
            gpio_set_value(led2, 0);
            break;
        case 3:
            gpio_set_value(led3, 0);
            break;
        default:
            printk(KERN_INFO"%s receive minor error.\n",__func__);
        }                       
    }
    else if(0x00 == buf)
    {
        switch(minor){
        case 0:
            gpio_set_value(led0, 1);
            break;
        case 1:
            gpio_set_value(led1, 1);
            break;
        case 2:
            gpio_set_value(led2, 1);
            break;
        case 3:
            gpio_set_value(led3, 1);
            break;
        default:
            printk(KERN_INFO"%s receive minor error\n",__func__);
        }       
    }
	
    return 0;  
}  


static struct file_operations leds_fops = {  
    .owner  =   THIS_MODULE,   
    .open   =   leds_drv_open,       
    .write  =   leds_drv_write,       
}; 

static int leds_probe(struct platform_device *pdev)  
{  
    struct device *dev = &pdev->dev;
    dev_t devid;
	
    printk(KERN_INFO"%s OK.\n",__func__);

    //1.申请设备号
    if(alloc_chrdev_region(&devid, 0, TI_LEDS_CNT, "ti_leds") < 0)
    {
        printk(KERN_INFO"%s ERROR.\n",__func__);
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
    led0 = of_get_named_gpio(dev->of_node, "am437x,led_gpio0", 0);;
    led1 = of_get_named_gpio(dev->of_node, "am437x,led_gpio1", 0);;
    led2 = of_get_named_gpio(dev->of_node, "am437x,led_gpio2", 0);;
    led3 = of_get_named_gpio(dev->of_node, "am437x,led_gpio3", 0);
	
    //printk(KERN_INFO"led0 = %d\n",led0);
    //printk(KERN_INFO"led1 = %d\n",led1);
    //printk(KERN_INFO"led2 = %d\n",led2);
    //printk(KERN_INFO"led3 = %d\n",led3);

    devm_gpio_request_one(dev, led0, GPIOF_OUT_INIT_HIGH, "LED0");
    devm_gpio_request_one(dev, led1, GPIOF_OUT_INIT_HIGH, "LED1");
    devm_gpio_request_one(dev, led2, GPIOF_OUT_INIT_HIGH, "LED2");
    devm_gpio_request_one(dev, led3, GPIOF_OUT_INIT_HIGH, "LED3");

error:
    unregister_chrdev_region(MKDEV(major, 0), TI_LEDS_CNT);	
	
    return 0;  
}  
  
static int leds_remove(struct platform_device *pdev)  
{  
    unsigned int i;
    printk(KERN_INFO"%s OK.\n",__func__);

    
    for(i=0;i<TI_LEDS_CNT;i++)
    {
        device_destroy(leds_cls,  MKDEV(major, i));	
    }
	
    class_destroy(leds_cls);
    cdev_del(&leds_cdev);
    unregister_chrdev(major, "ti_leds"); 
	
    return 0;  
}


static const struct of_device_id of_gpio_leds_match[] = {
	{ .compatible = "ti_leds", },
	{},
};

static struct platform_driver leds_drv = {
	.probe		= leds_probe,
	.remove		= leds_remove,
	.driver		= {
		.name	= "ti_am437x_leds_platform",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(of_gpio_leds_match),
	},
};


static int leds_drv_init(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    return platform_driver_register(&leds_drv);  
}  
  
static void leds_drv_exit(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    platform_driver_unregister(&leds_drv);  
}  


module_init(leds_drv_init);
module_exit(leds_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board leds drvice");
MODULE_ALIAS("platform:device tree:ti_leds");
MODULE_VERSION("V3.0");
