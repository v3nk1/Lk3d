/* eeprom.c - A small char driver to work with mini2440 eeprom
 *
 * Author: Veda Solutions (www.techveda.org)
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>
#include <linux/mod_devicetable.h>
#include <linux/log2.h>
#include <linux/bitops.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#define SIZE 64

#define COUNT 17

void read_eeprom(struct i2c_client *client)
{
	
	char off = 0x0, buf[SIZE];
	int ret;

	ret = i2c_master_send(client,&off,1);
	if(ret != 1)
	{
		pr_info("%s: ret=%d : i2c_master_send error\n",__func__,ret);
		return;
	}
	
	ret = i2c_master_recv(client,buf,SIZE);
	if(ret != SIZE)
	{
        	pr_info("%s: ret=%d : i2c_master_recv error", __func__,ret);
		return;
	}
	buf[SIZE-1] = '\0';
        pr_info("%s \n", buf);
	
}

int write_eeprom(struct i2c_client *client, char data)
{
	char buf[17];
	static char off=0x00;
	int ret=0;	
		
	/* Store the offset in first byte followed by data */
	buf[0]=off;
	memset(buf+1, data, 16);
	
	ret = i2c_master_send(client,buf,COUNT);
	if(ret!=COUNT)
	{
		pr_info("in %s: ret=%d i2c_master_send error\n",__func__,ret);
		return -1;
	}

	mdelay(10);
	off=off+16;
	
	return ret;
}

/*
 * Called by i2c-core when the i2c device with the address
 * 0x50 is found on the adapter.
 *
 * Inputs - client - i2c device pointer
 *          id     - the id that matched 
 * 
 * Return 0 on succefull probing, negative number
 * on failure
 */
static int eeprom_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{
	pr_info("%s\n",__func__);
	pr_info("In probe client add is %p\n",client);
	write_eeprom(client, 'A');
	write_eeprom(client, 'B');
	write_eeprom(client, 'C');
	write_eeprom(client, 'D');
	read_eeprom(client);
	return 0;	
}

/*Will be called from the i2c-core when our eeprom disappears*/
static int eeprom_remove(struct i2c_client *client)
{
	pr_info("driver removed\n");
	return 0;
}

/*Ask i2c-core for the device with address 0x50*/
static struct i2c_device_id eeprom_ids[] = {
        { "24c08",0x50 },  // mini2440 i2c device
	{ } // end of the list
};


static struct i2c_driver eeprom_driver = {
	.driver = {
		.name = "24c08",
		.owner = THIS_MODULE,
	},
	.probe = eeprom_probe,
	.remove = eeprom_remove,
	.id_table = eeprom_ids,
};

/*module initialization routine*/
static int __init eeprom_init(void)
{
	pr_info("%s\n",__func__);
	/*register with i2c-core*/
	return i2c_add_driver(&eeprom_driver);
}
module_init(eeprom_init);

static void __exit eeprom_exit(void)
{
	pr_info("%s\n",__func__);
	i2c_del_driver(&eeprom_driver);
}
module_exit(eeprom_exit);

MODULE_DESCRIPTION("Driver for I2C EEPROM");
MODULE_AUTHOR("Veda Solutions");
MODULE_LICENSE("GPL");
