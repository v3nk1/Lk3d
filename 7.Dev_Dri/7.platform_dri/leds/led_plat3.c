#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/path.h>
#include"led_hdr.h"
#include<linux/slab.h>
#include<linux/string.h>

#define DEV_NAME "led-4"

#define SUCCESS 0
#define FAILURE -1

static void *base, *config_reg, *data_reg, *up_reg;
static struct class *cls;
static int mjrno;

static int open(struct inode *in, struct file *fl)
{

	pr_info("%s: Invoked\n", __FUNCTION__);
	WRITE_REG(PULUP_EN, up_reg);
	return SUCCESS;

}

static ssize_t write(struct file *fl, const char __user * buf, size_t sz,
		     loff_t * off)
{
	char *kbuf;	
	int val;
	pr_info("%s: Invoked\n", __FUNCTION__);

	if (sz != 1)
		return -EINVAL;

	kbuf=memdup_user(buf,sz);
	if(!kbuf){
		pr_err("%s: memdup failed\n",__func__);
		return FAILURE;
		}
	pr_info("Size: %d, Data: %s\n", sz, buf);
	
	sscanf(kbuf, "%d", &val);
	if (val == 1 || val == 0) {
		WRITE_REG(CON_OUT, config_reg);
		WRITE_REG(val << DATA_SHIFT, data_reg);
	} else
		return FAILURE;

	return sz;
}

static int release(struct inode *in, struct file *fl)
{

	pr_info("%s: Invoked\n", __FUNCTION__);
	WRITE_REG(LED_OFF, data_reg);
	WRITE_REG(PULUP_DIS, up_reg);
	return SUCCESS;

}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = open,
	.write = write,
	.release = release
};

static int __init led_init(void)
{

	dev_t devid;

	pr_info("%s: Loaded\n", __FUNCTION__);

	base = ioremap(GPBCON, sizeof(int) * 3);
	if (!base) {
		pr_err("%s: ioremap: Failed\n", __func__);
		return FAILURE;
	}
	config_reg = base;
	data_reg = base + 4;
	up_reg = base + 8;

	if ((mjrno = register_chrdev(0, DEV_NAME, &fops)) < 0) {
		pr_info("%s: register_chrdev: Failed\n", __func__);
		return FAILURE;
	}
	pr_info("Major no: %d\n", mjrno);

	cls = class_create(THIS_MODULE, "VCLASS");

	if (!cls)
		pr_info("%s: class_create failed\n", __func__);

	devid = MKDEV(mjrno, 0);

	device_create(cls, NULL, devid, NULL, "led-4");

	return SUCCESS;

}

module_init(led_init);

static void __exit led_exit(void)
{

	dev_t devid;
	devid = MKDEV(mjrno, 0);
	device_destroy(cls, devid);

	class_destroy(cls);
	unregister_chrdev(mjrno, DEV_NAME);
	iounmap(base);
	pr_info("%s: Unloaded\n", __FUNCTION__);

}

module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Veda Solutions");
