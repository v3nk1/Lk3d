#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/path.h>
#include<linux/slab.h>
#include<linux/timer.h>

#include"led_hdr.h"

#define DEV_NAME "led_123"

#define SUCCESS 0
#define FAILURE -1

int lock;
#define LOCK 	1
#define UNLOCK	0


void *base,*config_reg,*data_reg,*up_reg;

struct timer_list ontimer;
struct timer_list offtimer;
int oncnt,offcnt;

void timer_func_on(unsigned long val){

	oncnt++;

	pr_info("val: %lu, oncnt: %d\n",val,oncnt);

	WRITE_REG(val<<DATA_SHIFT,data_reg);

if(oncnt<10)
	mod_timer(&ontimer,jiffies+HZ);

}

void timer_func_off(unsigned long val){

	offcnt++;
	pr_info("val: %lu, offcnt: %d\n",val,offcnt);

	WRITE_REG(val<<DATA_SHIFT,data_reg);	/* for LED_OFF*/

	if(offcnt<6)
        	mod_timer(&offtimer,jiffies+HZ*2);
		
}

int open(struct inode *in, struct file *fl){
	
	pr_info("%s: Invoked\n",__FUNCTION__);
	
	if(lock)	
		return -EBUSY;
	lock = LOCK;
	oncnt=0;/*resetting cnt val to 0*/
	offcnt=0;
	WRITE_REG(PULUP_EN,up_reg);
	return SUCCESS;

}

ssize_t write(struct file *fl,const char __user *buf,size_t sz, loff_t *off){

	int val;
	pr_info("%s: Invoked\n",__FUNCTION__);
	
        if(sz != 1) return -EINVAL;
	sscanf(buf,"%d",&val);
	
	if(val==1 || val == 0){
	
		WRITE_REG(CON_OUT,config_reg);
					/*To write a val in to data register we must configure config_reg as output*/

		ontimer.data = val;	/*Passing data to timer_func*/
		offtimer.data = 1;	/*for LED_OFF*/
		add_timer(&ontimer);
		add_timer(&offtimer);
		
		}
	else
		return FAILURE;

	return sz;

}

int release(struct inode *in,struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);

	WRITE_REG(LED_OFF,data_reg);		/*1 for LED_OFF*/
	WRITE_REG(PULUP_DIS,up_reg);
	lock = UNLOCK;

	return SUCCESS;

}


struct file_operations fops = {
				.owner = THIS_MODULE,
				.open = open,
				.write = write,
				.release = release
				};

struct class *cls;
int mjrno,minor = 1;  //Beware of local and global declarations since they shudnt match and shudnt redefined..

int __init init_module(void){

	dev_t devid;
	
	pr_info("%s: Loaded\n",__FUNCTION__);

	base = ioremap(GPBCON,sizeof(int)*3);
	
	config_reg = base;
	data_reg   = base+4;
	up_reg     = base+8;
	
	if((mjrno = register_chrdev(0,DEV_NAME,&fops))<0){ 
			pr_info("register_chrdev: Failed\n");
			return FAILURE;
			}

	pr_info("Major no: %d\n",mjrno);

	cls = class_create(THIS_MODULE,"VCLASS");
	
		if(!cls)
			pr_info("cls: ERROR\n");

		devid = MKDEV(mjrno,0);
		device_create(cls,NULL,devid,NULL,"led_dev");

	init_timer(&ontimer);
	init_timer(&offtimer);
	ontimer.function = timer_func_on;
	offtimer.function = timer_func_off;
	ontimer.expires = jiffies+HZ;
	offtimer.expires = jiffies+HZ*2;

	return SUCCESS;

}

void cleanup_module(void){

	dev_t devid;

	/*To make sure that LED's are OFF */
	WRITE_REG(LED_OFF,data_reg);		/*1 for LED_OFF*/
	WRITE_REG(PULUP_DIS,up_reg);

                devid = MKDEV(mjrno,0);
                device_destroy(cls,devid);
                
	class_destroy(cls);
	unregister_chrdev(mjrno,DEV_NAME);
	
	pr_info("%s: Unloaded\n",__FUNCTION__);

}

MODULE_LICENSE("GPL");
