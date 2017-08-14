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


/**************************************************
                    TI_BOARD
---------------------------------------------------
Ball     Color       Mode             Pin
---------------------------------------------------
H24     D7_Blue      0x07     uart3_txd(GPIO5_3)
H25     D8_Blue      0x07     uart3_rxd(GPIO5_2)
K24     D9_Green     0x07     uart3_rtsn(GPIO5_1)
H22     D10_Red      0x07     uart3_ctsn(GPIO5_0)
**************************************************/
static struct resource leds_resource[] = {  
    [0] = {  
        .start = 0x44DF8800,  
        .end   = 0x44DFFFFF, 
        .name  = "CM_PER",
        .flags = IORESOURCE_MEM,//PRCM_CM_PER_GPIO5_CLKCTRL(498h) CP141、469
    },  

    [1] = {  
        .start = 0x44E10000,  
        .end   = 0x44E1FFFF, 
        .name  = "CONTROL_MODULE",
        .flags = IORESOURCE_MEM,//CTRL_CONF_UART3_RXD(A28h)、CTRL_CONF_UART3_TXD(A2Ch)、CTRL_CONF_UART3_CTSN(A30h)、CTRL_CONF_UART3_RTSN((A34h)) CP142、643
	},	
    [2] = { 
        .start = 0x48322000,  
        .end   = 0x48322FFF, 
        .name  = "GOIP5",
        .flags = IORESOURCE_MEM,//GPIO_OE(134h)、GPIO_SETDATAOUT(194h)、GPIO_DATAOUT(13Ch) CP147、3713
	},
    [3] = { 
        .start = 0,  
        .end   = 3, 
        .name  = "GOIP5_PIN",
        .flags = IORESOURCE_IO,
	}

};  

static void leds_release(struct device * dev)  
{  

}

static struct platform_device leds_dev = {
    .name          = "ti_am437x_leds_platform",
    .id       	   = -1,  
    .num_resources = ARRAY_SIZE(leds_resource),  
    .resource      = leds_resource,  
    .dev = {   
    	.release = leds_release,   
    }, 	   
};

static int leds_dev_init(void)  
{  
    printk(KERN_INFO"leds_dev_init!\n");
    return platform_device_register(&leds_dev);;  
}  
  
static void leds_dev_exit(void)  
{  
    printk(KERN_INFO"leds_dev_exit!\n");
    platform_device_unregister(&leds_dev);  
}  
  

module_init(leds_dev_init);
module_exit(leds_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board leds drvice");
MODULE_ALIAS("platform:ti_leds");
MODULE_VERSION("V2.0");
