/*
 * Only for new kernels(> 3.10)
 */

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<linux/proc_fs.h>
#include<linux/mutex.h>
#include"RTC_HEADER.h"

#define SUCCESS  0
#define FAILURE -1

int RTC_open(struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__func__);
	return 0;

}

ssize_t read_time(struct file *fl, char __user *buf, size_t sz, loff_t *loff)
{	
	int hr=0x1,min=0x2,sec=0x00;
	int len;
	pr_info("%s: Invoked\n",__func__);
	len = sprintf(buf,"time: %x:%02x:%02x\n",hr,min,sec);

	return len;

}

        
ssize_t write_time(struct file *fl, const char __user *buffer, size_t sz, loff_t *loff)
{

	pr_info("%s: Invoked\n",__func__);
	return 0;
}


int RTC_release(struct inode *in, struct file *dfl){

	pr_info("%s: Invoked\n",__func__);
	return SUCCESS;

}

#define DIRNAME 		"RTC"
#define PROC_RW_TIME_ENTRY	"rw_time"

struct proc_dir_entry *pdep_parent;				/* RTC*/
struct proc_dir_entry *Time,*Date;				/* entities under RD_RTC & WR_RTC */

struct file_operations timefops={.owner=THIS_MODULE,
				 .open=RTC_open,
				 .read=seq_read,
				 .write=write_time,
				 .release=RTC_release
                                 };

int create_proc_entry_function(void){
	
	pdep_parent = proc_mkdir(DIRNAME,NULL);			/* RTC*/
		if(!pdep_parent){
			pr_info("failed to create directory\n");
			return FAILURE;
			}
	
	Time = proc_create(PROC_RW_TIME_ENTRY,0666,pdep_parent,&timefops);
				/*0666 is permissions for rwtime file in /proc */
		if(!Time){
			pr_info("failed to create proc_entry\n");
			return FAILURE;
			}
	return SUCCESS;
	
}


static int __init rd_rtc_register(void){

	pr_info("%s: invoked\n",__FUNCTION__);
	return create_proc_entry_function();
}

static void __exit rd_rtc_deregister(void){

	pr_info("%s: invoked\n",__FUNCTION__);

	remove_proc_entry(PROC_RW_TIME_ENTRY,pdep_parent);/*entities*/

//	remove_proc_entry(DIRNAME,NULL);/*MAIN DIR*/

}

module_init(rd_rtc_register);
module_exit(rd_rtc_deregister);

MODULE_LICENSE("GPL");
