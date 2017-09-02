#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>


static int at24cxx_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	printk(KERN_INFO"%s OK.\n",__func__); 
	return 0;
}

static int at24cxx_remove(struct i2c_client *client)
{
	//printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    printk(KERN_INFO"%s OK.\n",__func__); 
	return 0;
}

static const struct i2c_device_id at24cxx_id_table[] = {
	{ "at24c256", 0 },
	{}
};

/* 1. ����/����i2c_driver */
static struct i2c_driver at24cxx_driver = {
	.driver	= {
		.name	= "ti_i2c0",
		.owner	= THIS_MODULE,
	},
	.probe		= at24cxx_probe,
	.remove		= at24cxx_remove,
	.id_table	= at24cxx_id_table,//���������ƥ����
};

static int at24cxx_drv_init(void)
{
	/* 2. ע��i2c_driver */
    printk(KERN_INFO"%s OK.\n",__func__); 
	i2c_add_driver(&at24cxx_driver);//����һ��i2c�ӻ��豸
	
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


