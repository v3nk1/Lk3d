#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>

#define MAJORNO 300
#define MINORNO 0

#define DEV_NAME "/dev/my_cdev"

dev_t dev;
struct cdev *mycdev;

int my_cdrv_open(struct inode *ind, struct file *fl){
	
	pr_info("open: Opening a dev(%s)",DEV_NAME);
	return 0;
	
	}

ssize_t my_cdrv_read(struct file *fl, char __user *buf, size_t size, loff_t *len){

	pr_info("read: %s\n",buf);
	return 0;

}

ssize_t my_cdrv_write(struct file *fl, const char __user *buf, size_t size, loff_t *len){
	
	pr_info("Write: %s\n",buf);
	return 0;	

}
struct file_operations fops={.owner=THIS_MODULE,
			     .open=my_cdrv_open,
			     .read=my_cdrv_read,
			     .write=my_cdrv_write
			     };



int __init init_module(void){

	pr_info("my_cdev: module loaded\n");
        dev = MKDEV(MAJORNO,MINORNO);

	register_chrdev_region(dev,1,DEV_NAME);
	
	mycdev = cdev_alloc();
	cdev_init(mycdev,&fops);

	cdev_add(mycdev,dev,1);

	return 0;

}

void __exit cleanup_module(void){

	cdev_del(mycdev);
	unregister_chrdev_region(dev,1);

	pr_info("my_cdev: module removed\n");

}

MODULE_LICENSE("GPL");
