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

#include <linux/rtc.h>
#include <linux/pm_runtime.h>
#include <linux/bcd.h>

static struct rtc_device *rtc;

static void __iomem *am437x_rtc_base;

static int am437x_rtc_timer_irq = NO_IRQ;
static int am437x_rtc_alarm_irq = NO_IRQ;

static irqreturn_t rtc_irq(int irq, void *rtc)
{
	printk(KERN_INFO"%s OK.\n",__func__);

	return IRQ_HANDLED;
}

static int rtc_drv_open(struct device *dev)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct rtc_device *rtc_dev = platform_get_drvdata(pdev);
    int ret;

    printk(KERN_INFO"%s OK.\n",__func__);
/*
	if (devm_request_irq(&pdev->dev, am437x_rtc_timer_irq, rtc_irq, 0, dev_name(&rtc->dev), rtc)) {
		pr_debug("%s: RTC timer interrupt IRQ%d already claimed\n",pdev->name, am437x_rtc_timer_irq);
		goto fail0;
	}
	if ((am437x_rtc_timer_irq != am437x_rtc_alarm_irq) && 
        (devm_request_irq(&pdev->dev, am437x_rtc_alarm_irq, rtc_irq, 0, dev_name(&rtc->dev), rtc))) {
		pr_debug("%s: RTC alarm interrupt IRQ%d already claimed\n",pdev->name, am437x_rtc_alarm_irq);
		goto fail0;
	}
*/
    return 0;

fail0:
	return -EIO;
}

static int rtc_drv_release(struct device *dev)
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    
    return 0;
}


static int tm2bcd(struct rtc_time *tm)
{
	if (rtc_valid_tm(tm) != 0)
		return -EINVAL;

	tm->tm_sec  = bin2bcd(tm->tm_sec);
	tm->tm_min  = bin2bcd(tm->tm_min);
	tm->tm_hour = bin2bcd(tm->tm_hour);
	tm->tm_mday = bin2bcd(tm->tm_mday);

	tm->tm_mon  = bin2bcd(tm->tm_mon + 1);

	/* epoch == 1900 */
	if (tm->tm_year < 100 || tm->tm_year > 199)
		return -EINVAL;
	tm->tm_year = bin2bcd(tm->tm_year - 100);

	return 0;
}

static void bcd2tm(struct rtc_time *tm)
{
	tm->tm_sec  = bcd2bin(tm->tm_sec);
	tm->tm_min  = bcd2bin(tm->tm_min);
	tm->tm_hour = bcd2bin(tm->tm_hour);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon  = bcd2bin(tm->tm_mon) - 1;
	/* epoch == 1900 */
	tm->tm_year = bcd2bin(tm->tm_year) + 2000;
}

static void rtc_wait_not_busy(void)
{
	int	count = 0;
	u8	status;

	/* BUSY may stay active for 1/32768 second (~30 usec) */
	for (count = 0; count < 50; count++) {
		status = readb(am437x_rtc_base + 0x44);//STS
		if ((status & (0x01<<0)) == 0)
			break;
		udelay(1);
	}
	/* now we have ~15 usec to read/write various registers */
}

static int rtc_drv_read_time(struct device *dev, struct rtc_time *rtc_t)
{
    printk(KERN_INFO"%s OK.\n",__func__);

    //local_irq_disable();
	rtc_wait_not_busy();

	rtc_t->tm_sec  = readb(am437x_rtc_base + 0x00);
	rtc_t->tm_min  = readb(am437x_rtc_base + 0x04);
	rtc_t->tm_hour = readb(am437x_rtc_base + 0x08);
	rtc_t->tm_mday = readb(am437x_rtc_base + 0x0C);
	rtc_t->tm_mon  = readb(am437x_rtc_base + 0x10);
	rtc_t->tm_year = readb(am437x_rtc_base + 0x14);

	//local_irq_enable();

	bcd2tm(rtc_t);

    printk("\n\rcurrent_time is:\n\r\%d-%d-%d %d:%d:%d\n\r",\
            rtc_t->tm_year,rtc_t->tm_mon,rtc_t->tm_mday,rtc_t->tm_hour,rtc_t->tm_min,rtc_t->tm_sec);

    return 0;
}

static int rtc_drv_set_time(struct device *dev, struct rtc_time *rtc_t)
{
    if (tm2bcd(rtc_t) < 0)
		return -EINVAL;
    
	//local_irq_disable();
	rtc_wait_not_busy();

	writeb(rtc_t->tm_sec, am437x_rtc_base + 0x00);
    writeb(rtc_t->tm_min, am437x_rtc_base + 0x04);
	writeb(rtc_t->tm_hour, am437x_rtc_base + 0x08);
	writeb(rtc_t->tm_mday, am437x_rtc_base + 0x0C);
	writeb(rtc_t->tm_mon, am437x_rtc_base + 0x10);
	writeb(rtc_t->tm_year, am437x_rtc_base + 0x14);

	//local_irq_enable();

    return 0;
}

static int rtc_drv_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
    printk(KERN_INFO"%s OK.\n",__func__);
	
    return 0;
}
static int rtc_drv_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
    printk(KERN_INFO"%s OK.\n",__func__);
    return 0;
}

static int rtc_drv_proc(struct device *dev, struct seq_file *seq)
{
    printk(KERN_INFO"%s OK.\n",__func__);
    return 0;
}

static int rtc_drv_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	
    printk(KERN_INFO"%s OK.\n",__func__);
	return 0;
}

static struct rtc_class_ops am437x_rtc_ops = {   
    .open       = rtc_drv_open,       
    .release    = rtc_drv_release,
    .read_time  = rtc_drv_read_time,
    .set_time   = rtc_drv_set_time,
    .read_alarm = rtc_drv_read_alarm,
    .set_alarm  = rtc_drv_set_alarm,
    .proc       = rtc_drv_proc, 
    .alarm_irq_enable  = rtc_drv_alarm_irq_enable, 
}; 

static void am437x_rtc_enable(struct platform_device *pdev, int en)
{
    void __iomem *rtc_base  = am437x_rtc_base;
    
	unsigned int tmp;

	if (am437x_rtc_base == NULL)
		return;
    
	if (en) {
        
        /* Enable the clock/module so that we can access the registers */
	    pm_runtime_get_sync(&pdev->dev);
        
        //rtc init.
        tmp = readb(rtc_base + 0x40);//CTRL.Enable the RTC module
        writew(tmp & ~(0x01<<6), rtc_base + 0x40);

        writel(0x83E70B13, rtc_base + 0x6C);//KICK0R.Write Project Disable
        writel(0x95A4F1E0, rtc_base + 0x70);//KICK1R

        tmp = readb(rtc_base + 0x54);//OSC.mode1:Internal clock 
        writew(tmp & ~(0x01<<3), rtc_base + 0x54);
        tmp = readb(rtc_base + 0x54);
        writew(tmp | (0x01<<6), rtc_base + 0x54);
        
        tmp = readb(rtc_base + 0x40);//run.
        writew(tmp | (0x01<<0), rtc_base + 0x40);
	} 
    else {
        tmp = readb(rtc_base + 0x40);//stop.
        writew(tmp & ~(0x01<<0), rtc_base + 0x40);
    
        tmp = readb(rtc_base + 0x40);//CTRL.Disable the RTC module
        writew(tmp | (0x01<<6), rtc_base + 0x40); 

        /* Disable the clock/module */
	    pm_runtime_put_sync(&pdev->dev);
	}
}

struct resource *am437x_rtc_mem;

static int am437x_rtc_probe(struct platform_device *pdev)  
{  
	struct resource *res;
    
	int ret;   
    
    printk(KERN_INFO"%s OK.\n",__func__);
    
    /* find the IRQs */
    am437x_rtc_timer_irq = platform_get_irq(pdev, 0);
	if (am437x_rtc_timer_irq < 0) {
		dev_err(&pdev->dev, "no irq for rtc tick\n");
		return am437x_rtc_timer_irq;
	}
    
    am437x_rtc_alarm_irq = platform_get_irq(pdev, 1);
	if (am437x_rtc_alarm_irq < 0) {
		dev_err(&pdev->dev, "no irq for alarm\n");
		return am437x_rtc_alarm_irq;
	}
    
    dev_dbg(&pdev->dev, "am437x_rtc: tick irq %d, alarm irq %d\n",
		 am437x_rtc_timer_irq, am437x_rtc_alarm_irq);
       
    /*RTC*/
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if(res == NULL){
        dev_err(&pdev->dev, "RTC:failed to get memory regin resource.\n");
        return -ENOENT;
    }
    
    am437x_rtc_mem = request_mem_region(res->start, res->end - res->start+1, pdev->name);
    if (am437x_rtc_mem == NULL){
        dev_err(&pdev->dev, "RTC:failed to reserve memory region.\n");
        return -ENOENT;
        goto err_nores;
    }

    am437x_rtc_base = ioremap(res->start, res->end - res->start+1);
    if (am437x_rtc_mem == NULL){
        dev_err(&pdev->dev, "RTC:failed ioremap.\n");
        return -EINVAL;
        goto err_nomap;
    }

    am437x_rtc_enable(pdev, 1);
    
	rtc = devm_rtc_device_register(&pdev->dev, pdev->name,&am437x_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc)) {
		pr_debug("%s: can't register RTC device, err %ld\n",pdev->name, PTR_ERR(rtc));
		goto err_nortc;
	}

    return 0;
    
err_nortc:
    am437x_rtc_enable(pdev, 0);
    iounmap(am437x_rtc_base);
    
err_nomap:
    release_resource(am437x_rtc_mem);
    
err_nores:
    return ret;
}

static int __exit am437x_rtc_remove(struct platform_device *pdev)
{
    printk(KERN_INFO"%s OK.\n",__func__);

    am437x_rtc_enable(pdev, 0);
    devm_rtc_device_unregister(&pdev->dev, rtc);
    release_resource(am437x_rtc_mem);
    iounmap(am437x_rtc_base);

	return 0;
}

struct platform_driver am437x_rtc_drv = { 
	.probe		= am437x_rtc_probe,
    .remove		= __exit_p(am437x_rtc_remove),
	.driver		= {
		.name	= "ti_am437x_rtc_platform",
   		.owner	= THIS_MODULE,
	},
};

static int rtc_drv_init(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    return platform_driver_register(&am437x_rtc_drv);  
}  

static void rtc_drv_exit(void)  
{  
    printk(KERN_INFO"%s OK.\n",__func__);
    platform_driver_unregister(&am437x_rtc_drv);  
}  

module_init(rtc_drv_init);
module_exit(rtc_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board rtc drvice");
MODULE_ALIAS("platform:ti_rtc");
MODULE_VERSION("V2.0");
