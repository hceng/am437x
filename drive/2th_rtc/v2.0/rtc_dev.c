#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/platform_device.h>

static struct resource am437x_rtc_resource[] = {  
    [0] = {  
        .name  = "RTCSS",
        .start = 0x44E3E000,  
        .end   = 0x44E3EFFF, 
        .flags = IORESOURCE_MEM,
    },  

    [1] = {  
        .name  = "RTCINT",
        .start = 107,  
        .end   = 107, 
        .flags = IORESOURCE_IRQ,//107
    },	

    [2] = { 
        .name  = "RTCALARMINT",
        .start = 108,  
        .end   = 108, 
        .flags = IORESOURCE_IRQ,//108
    },
};  


static void am437x_rtc_release(struct device * dev)
{
    return ;
}

static struct platform_device am437x_rtc_dev = {
    .name          = "ti_am437x_rtc_platform",
    .id       	   = -1,  
    .num_resources = ARRAY_SIZE(am437x_rtc_resource),  
    .resource      = am437x_rtc_resource,  
    .dev = {
        .release   = am437x_rtc_release,  
    }
      
};

static int rtc_dev_init(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    return platform_device_register(&am437x_rtc_dev);;  
}  

static void rtc_dev_exit(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    platform_device_unregister(&am437x_rtc_dev);  
}  


module_init(rtc_dev_init);
module_exit(rtc_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board rtc drvice");
MODULE_ALIAS("platform:ti_rtc");
MODULE_VERSION("V2.0");
