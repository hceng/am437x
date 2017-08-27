#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define TI_RTC_CNT     1

int major;
static struct cdev rtc_cdev;
static struct class *rtc_cls;

static volatile unsigned long *PRCM_CM_RTC_CLKCTRL   = NULL;  
static volatile unsigned long *PRCM_CM_RTC_CLKSTCTRL = NULL;  
static volatile unsigned long *RTCSS_BASE            = NULL;
static volatile unsigned long *RTCSS_CTRL            = NULL;
static volatile unsigned long *RTCSS_KICK0R          = NULL;
static volatile unsigned long *RTCSS_KICK1R          = NULL; 
static volatile unsigned long *RTCSS_OSC             = NULL;
static volatile unsigned long *RTCSS_YEARS           = NULL; 
static volatile unsigned long *RTCSS_MONTHS          = NULL;
static volatile unsigned long *RTCSS_WEEKS           = NULL; 
static volatile unsigned long *RTCSS_DAYS            = NULL;
static volatile unsigned long *RTCSS_HOURS           = NULL; 
static volatile unsigned long *RTCSS_MINUTES         = NULL;
static volatile unsigned long *RTCSS_SECONDS         = NULL; 
static volatile unsigned long *RTCSS_ALARM_YEARS     = NULL; 
static volatile unsigned long *RTCSS_ALARM_MONTHS    = NULL; 
static volatile unsigned long *RTCSS_ALARM_DAYS      = NULL;
static volatile unsigned long *RTCSS_ALARM_HOURS     = NULL; 
static volatile unsigned long *RTCSS_ALARM_MINUTES   = NULL;
static volatile unsigned long *RTCSS_ALARM_SECONDS   = NULL; 

struct rtc_struct {
	int year;
	int month;
	//int week;
	int day;
	int hour;
	int minute;
	int second;
};

static int rtc_drv_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO"%s OK.\n",__func__);   
    
    *PRCM_CM_RTC_CLKCTRL   &= ~(0x03<<0);
	*PRCM_CM_RTC_CLKCTRL   |=  (0x01<<1);
	*PRCM_CM_RTC_CLKSTCTRL &= ~(0x03<<0);
    
    *RTCSS_CTRL &= ~(0x01<<6);
    
    *RTCSS_KICK0R = (0x83E70B13);
	*RTCSS_KICK1R = (0x95A4F1E0);
    
    *RTCSS_OSC  &= ~(0x01<<3);
	*RTCSS_OSC  |=  (0x01<<6);
    *RTCSS_CTRL |=  (0x01<<0);
    
    return 0;     
}

static ssize_t rtc_drv_read_time(struct file *file, char __user *user_buf, size_t size, loff_t *ppos)
{
    struct rtc_struct rtc_time;
    
    printk(KERN_INFO"%s OK.\n",__func__);  
    
    rtc_time.year   = (((*RTCSS_YEARS   & (0x03<<4))>>4)*10 + (*RTCSS_YEARS   & (0x0F<<0)));
 	rtc_time.month  = (((*RTCSS_MONTHS  & (0x07<<4))>>4)*10 + (*RTCSS_MONTHS  & (0x0F<<0)));
	rtc_time.day    = (((*RTCSS_DAYS    & (0x07<<4))>>4)*10 + (*RTCSS_DAYS    & (0x0F<<0)));
	rtc_time.hour   = (((*RTCSS_HOURS   & (0x03<<4))>>4)*10 + (*RTCSS_HOURS   & (0x0F<<0)));
	rtc_time.minute = (((*RTCSS_MINUTES & (0x07<<4))>>4)*10 + (*RTCSS_MINUTES & (0x0F<<0)));
	rtc_time.second = (((*RTCSS_SECONDS & (0x07<<4))>>4)*10 + (*RTCSS_SECONDS & (0x0F<<0)));

    copy_to_user(user_buf, &rtc_time, sizeof(rtc_time)); 
    
    return 0;     
}
static ssize_t rtc_drv_set_time(struct file *file, const char __user *user_buf, size_t count, loff_t * ppos)
{
    struct rtc_struct rtc_time;
    
    printk(KERN_INFO"%s OK.\n",__func__);
    
    if(count != sizeof(rtc_time)){
        printk(KERN_INFO"write count != %d.\n",sizeof(rtc_time)); 
        return 1;
    }
 
    if (copy_from_user(&rtc_time, user_buf, count))
        return -EFAULT;
    
    *RTCSS_CTRL &= ~(0x01<<0);//stop
    
    if((rtc_time.year-2000) > 99 || (rtc_time.year-2000) < 0)
		goto err;
    
	if(rtc_time.month > 12 || rtc_time.month < 0)
		goto err;
	*RTCSS_MONTHS = ((rtc_time.month/10) << 4) | ((rtc_time.month%10) << 0);

	if(rtc_time.day > 32 || rtc_time.day < 0)
		goto err;
	*RTCSS_DAYS = ((rtc_time.day/10) << 4) | ((rtc_time.day%10) << 0);	

	if(rtc_time.hour > 23 || rtc_time.hour < 0)
		goto err;
	*RTCSS_HOURS = ((rtc_time.hour/10) << 4) | ((rtc_time.hour%10) << 0);

	if(rtc_time.minute > 59 || rtc_time.minute < 0)
		goto err;
	*RTCSS_MINUTES = ((rtc_time.minute/10) << 4) | ((rtc_time.minute%10) << 0);

	if(rtc_time.second > 59 || rtc_time.second < 0)
		goto err;
	*RTCSS_SECONDS = ((rtc_time.second/10) << 4) | ((rtc_time.second%10) << 0);

	*RTCSS_CTRL |= (0x01<<0);//start
    
    return 0; 

err:
	printk(KERN_INFO"rtc_drv_set_time err.\n");  
    
    return 1;  
}

static struct file_operations rtc_fops = {
    .owner  =   THIS_MODULE,  
    .open   =   rtc_drv_open,    
    .read   =   rtc_drv_read_time,	     
    .write  =   rtc_drv_set_time,	   
};

static int rtc_drv_init(void)
{
    dev_t devid;
    
    printk(KERN_INFO"%s OK.\n",__func__);

    if(alloc_chrdev_region(&devid, 0, TI_RTC_CNT, "ti_rtc") < 0)
    {
        printk(KERN_INFO"%s ERROR.\n",__func__);
        goto error;
    }

    major = MAJOR(devid);

    cdev_init(&rtc_cdev, &rtc_fops);        
    cdev_add(&rtc_cdev, devid, TI_RTC_CNT);   

    rtc_cls = class_create(THIS_MODULE, "ti_rtc");

    device_create(rtc_cls, NULL, MKDEV(major, 0), NULL, "ti_rts0"); 

    PRCM_CM_RTC_CLKSTCTRL = ioremap(0x44DF8500+0x00, 0x04*1);
    PRCM_CM_RTC_CLKCTRL   = ioremap(0x44DF8500+0x20, 0x04*1);
    
    RTCSS_BASE            = ioremap(0x44E3E000, 0xA0);
    RTCSS_SECONDS         = RTCSS_BASE + 0;      
    RTCSS_MINUTES         = RTCSS_BASE + 1; 
    RTCSS_HOURS           = RTCSS_BASE + 2;  
    RTCSS_DAYS            = RTCSS_BASE + 3;
    RTCSS_WEEKS           = RTCSS_BASE + 4; 
    RTCSS_MONTHS          = RTCSS_BASE + 5;
    RTCSS_YEARS           = RTCSS_BASE + 6;  
    RTCSS_ALARM_SECONDS   = RTCSS_BASE + 8;  
    RTCSS_ALARM_MINUTES   = RTCSS_BASE + 9; 
    RTCSS_ALARM_HOURS     = RTCSS_BASE + 10;
    RTCSS_ALARM_DAYS      = RTCSS_BASE + 11; 
    RTCSS_ALARM_MONTHS    = RTCSS_BASE + 12; 
    RTCSS_ALARM_YEARS     = RTCSS_BASE + 13;      
    RTCSS_CTRL            = RTCSS_BASE + 15; 
    RTCSS_OSC             = RTCSS_BASE + 20;    
    RTCSS_KICK0R          = RTCSS_BASE + 25;      
    RTCSS_KICK1R          = RTCSS_BASE + 26;      
   
error:
    unregister_chrdev_region(MKDEV(major, 0), TI_RTC_CNT);

    return 0;
}

static void rtc_drv_exit(void)
{
    unsigned i;
    printk(KERN_INFO"%s OK.\n",__func__);

    for(i=0;i<TI_RTC_CNT;i++)
    {
        device_destroy(rtc_cls,  MKDEV(major, i));	
    }
    class_destroy(rtc_cls);
    cdev_del(&rtc_cdev);
    unregister_chrdev(major, "ti_rtc"); 

    iounmap(PRCM_CM_RTC_CLKSTCTRL); 
    iounmap(PRCM_CM_RTC_CLKCTRL);   
    iounmap(RTCSS_BASE);            
}

module_init(rtc_drv_init);
module_exit(rtc_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board rtc drvice");
MODULE_ALIAS("character device:ti_rtc");
MODULE_VERSION("V1.0");
