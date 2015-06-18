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
#include <asm/string.h>

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
	u8 off = 0x0, buf[SIZE]={};
	int ret,i;
	if(lbuf > 256)
		return -1;

	for(i=0;i<lbuf/2+1;i++){
		ret = i2c_smbus_read_word_data(info.client,off+i*2);
		if(ret < 0){
        		pr_info("%s: ret=%d : i2c_master_recv error\n", __func__,ret);
			return -1;
			}
		memcpy(buf+2*i,&ret,2);
		mdelay(10);	
	}
	pr_info("read: data red: %02x %2x\n",buf[0],buf[1]);
	buf[lbuf] = '\0';

	ret = lbuf - copy_to_user(ubuf, buf, lbuf);
	return ret;
}

ssize_t eeprom_write(struct file *file, const char __user *ubuf, size_t lbuf, loff_t * offset)
{

	unsigned char *kbuf,off=0x00;
	int ret=0,i=0;
	u16 send;	
	if(lbuf > 256)
                return -1;
	kbuf = kmalloc(lbuf+1, GFP_KERNEL);
	if(!kbuf)
		return -1;

	copy_from_user(kbuf, ubuf, lbuf);

	pr_info("got text: %s\n",kbuf);
//	for(i=0;i<lbuf/2+1;i++){
		pr_info("to be written %c %c\n",kbuf[i*2],kbuf[1+i*2]);
		ret=i2c_smbus_write_block_data(info.client,off+i*2,2,kbuf+i*2);
                if(ret<0){
                        pr_err("smbus block write failed\n");
                        return -1;
                        }
		pr_info("#i=%d\n",i);
		mdelay(10);

//		}
/*
        for(i=0;i<lbuf/2+1;i++){
		memcpy(&send,kbuf+2*i,2);
		ret=i2c_smbus_write_word_data(info.client,off+i*2,send);
		if(ret<0){
			pr_err("smbus block write failed\n");
			return -1;
			}
//	pr_info("#i=%d\n",i);
		mdelay(10);
	}
*/
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
	
	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_READ_BYTE))
		pr_alert("no I2C_FUNC_SMBUS_READ_BYTE\n");
             
	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_WRITE_BYTE))
	        pr_alert("no I2C_FUNC_SMBUS_WRITE_BYTE\n");


	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_READ_BYTE_DATA))
		pr_alert("no I2C_FUNC_SMBUS_READ_BYTE_DAT\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		pr_alert("no I2C_FUNC_SMBUS_WRITE_BYTE_DATA\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_READ_WORD_DATA))
		pr_alert("no I2C_FUNC_SMBUS_READ_WORD_DATA\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_WRITE_WORD_DATA))
		pr_alert("no I2C_FUNC_SMBUS_WRITE_WORD_DATA\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		pr_alert("no I2C_FUNC_SMBUS_READ_BLOCK_DATA\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_WRITE_BLOCK_DATA))
		pr_alert("no I2C_FUNC_SMBUS_WRITE_BLOCK_DATA\n");
		
	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_READ_I2C_BLOCK))
                pr_alert("No I2C_FUNC_SMBUS_READ_I2C_BLOCK\n");

	if(!i2c_check_functionality(client->adapter,I2C_FUNC_SMBUS_WRITE_I2C_BLOCK))
                pr_alert("No I2C_FUNC_SMBUS_WRITE_I2C_BLOCK\n");


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
