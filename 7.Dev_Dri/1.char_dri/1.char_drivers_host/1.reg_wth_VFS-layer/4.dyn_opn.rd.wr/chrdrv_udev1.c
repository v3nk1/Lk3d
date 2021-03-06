#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>

#include<asm/uaccess.h>

#define FAILURE -1
#define CHRDRV_NAME "/dev/cdev"  //this entry will appears in cat /proc/devices

dev_t devid;
struct cdev *cdevp;

int cdev_close (struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;

}

ssize_t cdev_read (struct file *fl, char __user *buf, size_t sz, loff_t *lf){

	copy_to_user(buf,"uread: invoked\0",sz);
	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;

}

ssize_t cdev_write (struct file *fl, const char __user *buf, size_t sz, loff_t *lf){
	
	char devwr_msg[100];
	pr_info("%s: Invoked\n",__FUNCTION__);
	copy_from_user(devwr_msg,buf,sizeof(devwr_msg));
	pr_info("devwrmsg: %s\n",devwr_msg);
	return 0;

}


struct file_operations fops1={
                                .owner  = THIS_MODULE,
                                .read         = cdev_read,
                                .write        = cdev_write,
                                .release= cdev_close

                        };


int cdev_open (struct inode *in, struct file *fl){
	
	pr_info("%s: Invoked\n",__FUNCTION__);
	fl->f_op=&fops1;
	return 0;	

}


struct file_operations fops={
				.owner 	= THIS_MODULE,
				.open 	= cdev_open,
				//.read 	= cdev_read,
				//.write	= cdev_write,
				//.release= cdev_close
			
			};

struct device *devp;
struct class *clas;

static int __init chrdrv_init(void){

	int base_minorno = 0;
	pr_info("chrdrv: Registered\n");
	
/*Registering MAJOR and MINOR no's */
	if(alloc_chrdev_region(&devid,base_minorno,1,CHRDRV_NAME)<0){//searchs majorno which is free at that time dymanically and combines it our given minorno and finally populate devid with maj&minor(since it call by reference)
			pr_info("failed to register maj,min no..\n");
			return FAILURE;
			}
	
	pr_info("MAJOR: %d, MINOR: %d\n",MAJOR(devid),MINOR(devid));


/*1st create a class in /sys/VIRTUAL	then

Create a device node for aquired major and minor no.. dynamincally using udev userspace deamon. U can see it in "ls /sys/class/VIRTUAL" or ls /dev */	
	clas = class_create(THIS_MODULE,"VIRTUAL");
	devp = device_create(clas,NULL,devid,NULL,"%s%i","vdev",123);

/* Registering our routines with VFS	*/
	cdevp = cdev_alloc();/*Allocates a structure object for cdev*/
	cdev_init(cdevp,&fops);
	if(cdev_add(cdevp,devid,1)<0)
			pr_info("cdev_add: Failed\n");

	return 0;	

}

static void __exit chrdrv_cleanup(void){

	pr_info("chrdrv: Unloaded\n");

/* Must invoke bellow stuff same order, Otherwise kernel will crash, else shud restart	*/
	device_destroy(clas,devid);
	class_destroy(clas);
	cdev_del(cdevp);
	unregister_chrdev_region(devid,1);

}

module_init(chrdrv_init);
module_exit(chrdrv_cleanup);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("F*CK");
