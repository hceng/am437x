#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

#define TI_EEPROM_CNT     1

static int major;
static struct cdev at24cxx_cdev;
static struct class *at24cxx_cls;
static struct i2c_client *at24cxx_client;

/* 
 * 传入: buf[0] : addr
 * 输出: buf[0] : data
 */
static ssize_t at24cxx_read(struct file * file, char __user *user_buf, size_t count, loff_t *off)
{
    unsigned char addr, data;
    char send[2];
    int ret;

    if(count != 1){
        printk(KERN_INFO"at24cxx_read count != 1.\n"); 
        return 1;
    }

    if (copy_from_user(&addr, user_buf, count))
        return -EFAULT;

    send[0] = addr>>8;
    send[1] = addr;

    i2c_master_send(at24cxx_client, send, 2);

    i2c_master_recv(at24cxx_client, &data, 1);

    ret = copy_to_user(user_buf, &data, 1);

    return 1;
}

/* buf[0] : addr
 * buf[1] : data
 */
static ssize_t at24cxx_write(struct file *file, const char __user *user_buf, size_t count, loff_t *off)
{
    unsigned char ker_buf[2];
    char send[3];

    printk(KERN_INFO"%s OK.\n",__func__);

    if(count != 2){
        printk(KERN_INFO"at24cxx_write count != 2.\n"); 
        return 1;
    }

    if (copy_from_user(&ker_buf, user_buf, count))
        return -EFAULT;

    //printk("ker_buf[0]= 0x%02x, ker_buf[1]= x%02x\n", ker_buf[0], ker_buf[1]);

    send[0] = ker_buf[0]>>8;
    send[1] = ker_buf[0];
    send[2] = ker_buf[1];

    if(i2c_master_send(at24cxx_client, send, 3))
        return 2;
    else 
        return -EIO;
}

static struct file_operations at24cxx_fops = {
    .owner = THIS_MODULE,
    .read  = at24cxx_read,
    .write = at24cxx_write,
};

static int at24cxx_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    dev_t devid;
    at24cxx_client = client;

    printk(KERN_INFO"%s OK.\n",__func__); 

    //1.申请设备号
    if(alloc_chrdev_region(&devid, 0, TI_EEPROM_CNT, "at24cxx") < 0)
    {
        printk(KERN_INFO"%s ERROR.\n",__func__);
        goto error;
    }
    major = MAJOR(devid);

    //2.注册到系统中
    cdev_init(&at24cxx_cdev, &at24cxx_fops);        
    cdev_add(&at24cxx_cdev, devid, TI_EEPROM_CNT);   
    at24cxx_cls = class_create(THIS_MODULE, "ti_at24cxx");
    device_create(at24cxx_cls, NULL, MKDEV(major, 0), NULL, "at24cxx");    

error:
    unregister_chrdev_region(MKDEV(major, 0), TI_EEPROM_CNT);	

    return 0;
}

static int at24cxx_remove(struct i2c_client *client)
{
    unsigned int i;

    printk(KERN_INFO"%s OK.\n",__func__); 

    for(i=0;i<TI_EEPROM_CNT;i++)
    {
        device_destroy(at24cxx_cls,  MKDEV(major, i));	
    }
    class_destroy(at24cxx_cls);

    unregister_chrdev(major, "at24cxx");

    return 0;
}

static const struct i2c_device_id at24cxx_id_table[] = {
    { "at24c256", 0 },
    {}
};


/* 1. 分配/设置i2c_driver */
static struct i2c_driver at24cxx_driver = {
    .driver	= {
        .name	= "ti_i2c0",
        .owner	= THIS_MODULE,
    },
    .probe		= at24cxx_probe,
    .remove		= at24cxx_remove,
    .id_table	= at24cxx_id_table,
};

static int at24cxx_drv_init(void)
{
    /* 2. 注册i2c_driver */
    printk(KERN_INFO"%s OK.\n",__func__); 

    i2c_add_driver(&at24cxx_driver);

    return 0;
}

static void at24cxx_drv_exit(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 

    i2c_del_driver(&at24cxx_driver);
}


module_init(at24cxx_drv_init);
module_exit(at24cxx_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board i2c drvice to at24c256");
MODULE_ALIAS("platform:device tree:ti_i2c");
MODULE_VERSION("V1.0");


