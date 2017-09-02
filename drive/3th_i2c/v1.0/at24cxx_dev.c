#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>


static struct i2c_board_info at24cxx_info = {	
	I2C_BOARD_INFO("at24c256", 0x50),
};

static struct i2c_client *at24cxx_client;

static int at24cxx_dev_init(void)
{
	struct i2c_adapter *i2c_adap;
    
    printk(KERN_INFO"%s OK.\n",__func__); 

	i2c_adap = i2c_get_adapter(0);//获取一个设配器(I2C控制器)——i2c0
	at24cxx_client = i2c_new_device(i2c_adap, &at24cxx_info);//创建一个I2C从机设备，指定设配器和从机信息。且认为0x50地址的设备肯定存在
	i2c_put_adapter(i2c_adap);//挂起适配器
	
	return 0;
}

static void at24cxx_dev_exit(void)
{
    printk(KERN_INFO"%s OK.\n",__func__); 
	i2c_unregister_device(at24cxx_client);
}


module_init(at24cxx_dev_init);
module_exit(at24cxx_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hceng <huangcheng.job@foxmail.com>");
MODULE_DESCRIPTION("TI am437x board i2c device to at24c256");
MODULE_ALIAS("platform:device tree:ti_i2c");
MODULE_VERSION("V1.0");


