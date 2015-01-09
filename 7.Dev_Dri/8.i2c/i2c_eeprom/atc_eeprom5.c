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
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#define SIZE 256
#define SUCCESS 0
#define COUNT 17
#define DEV_NAME "eeprom_dev"

struct eeprom_private {
	struct i2c_client *client;
	int inuse;
};
struct eeprom_private info;



ssize_t eeprom_read(struct file *file,char __user *ubuf, size_t lbuf, loff_t * offset)
{ 	
	char off = 0x0, buf[SIZE];
	int ret;
	if(lbuf > 256)
		return -1;
	ret = i2c_master_send(info.client,&off,1);
	if(ret != 1)
	{
		pr_info("%s: ret=%d : i2c_master_send error\n",__func__,ret);
		return -1;
	}
	
	ret = i2c_master_recv(info.client,buf,lbuf);
	if(ret != lbuf)
	{
        	pr_info("%s: ret=%d : i2c_master_recv error", __func__,ret);
		return -1;
	}
	buf[lbuf] = '\0';

	ret = lbuf - copy_to_user(ubuf, buf, lbuf);
	return ret;
}




ssize_t eeprom_write(struct file *file, const char __user *ubuf, size_t lbuf, loff_t * offset)
{
	char buf[17], *kbuf;
	static char off=0x00;
	int ret=0;
	
	int i,cnt;

	kbuf = kmalloc(lbuf, GFP_KERNEL);
	if(!kbuf)
		return -1;

	copy_from_user(kbuf, ubuf, lbuf);

	cnt = lbuf/0x10 + 1;	
	for(i=0; i<cnt; i++) {
		/* Store the offset in first byte followed by data */
		buf[0]=off;
		strncpy(buf+1, kbuf+off, 16);
	
		ret = i2c_master_send(info.client,buf,COUNT);
		if(ret!=COUNT)
		{
			pr_info("in %s: ret=%d i2c_master_send error\n",__func__,ret);
			return -1;
		}

		mdelay(10);
		off=off+16;
	}
	kfree(kbuf);
	return ret;
}

static int char_dev_open(struct inode *inode, struct file *file)
{
        if (info.inuse) {
                pr_err("Device busy %s\n", DEV_NAME);
                return -EBUSY;
        }
        info.inuse = 1;
        pr_info("Open operation invoked\n");
        return SUCCESS;
}

static int char_dev_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n",__func__);
        info.inuse = 0;
        return SUCCESS;
}


static struct file_operations char_dev_fops = {
        .owner = THIS_MODULE,
        .open = char_dev_open,
        .release = char_dev_release,
        .write = eeprom_write,
	.read = eeprom_read,
};

static struct miscdevice eeprom_misc = {
        .minor = MISC_DYNAMIC_MINOR,    /* allocate misc minor */
        .name = DEV_NAME,
        .fops = &char_dev_fops,         /* drivers fops instance */
};

static int eeprom_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{
	int ret;
	pr_info("%s\n",__func__);
	info.client = client;
	ret = misc_register(&eeprom_misc);
        if (ret < 0) {
                pr_err("failed registering with minor %d", eeprom_misc.minor);
                return ret;
        }
	pr_info("In probe client add is %p\n",client);
	return 0;	
}

/*Will be called from the i2c-core when our eeprom disappears*/
static int eeprom_remove(struct i2c_client *client)
{
	misc_deregister(&eeprom_misc);
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
