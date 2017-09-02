#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>


static const unsigned short addr_list[] = { 0x60, 0x50, I2C_CLIENT_END };

static struct i2c_client *at24cxx_client;

static int at24cxx_dev_init(void)
{
	struct i2c_adapter *i2c_adap;
    struct i2c_board_info at24cxx_info;
    
    printk(KERN_INFO"%s OK.\n",__func__); 
    
    memset(&at24cxx_info, 0, sizeof(struct i2c_board_info));	
	strlcpy(at24cxx_info.type, "at24c256", I2C_NAME_SIZE);

	i2c_adap = i2c_get_adapter(0);//i2c0
	at24cxx_client = i2c_new_probed_device(i2c_adap, &at24cxx_info, addr_list, NULL);
	i2c_put_adapter(i2c_adap);
	
    if (at24cxx_client)
    {
        printk(KERN_INFO"at24cxx_client = 0x%x OK.\n", at24cxx_client->addr);   
        return 0; 
    }
		
	else
    {
        printk(KERN_INFO"at24cxx_client = 0x%x Error.\n", at24cxx_client->addr);  
        return -ENODEV;
    }
		 
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
MODULE_VERSION("V2.0");


