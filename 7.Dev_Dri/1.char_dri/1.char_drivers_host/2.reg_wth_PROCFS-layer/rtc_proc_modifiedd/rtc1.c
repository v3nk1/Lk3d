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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	
	#define USE

#endif

/**
 * Kernel version:(< 3.10)
 *
 * When you register proc-entry, proc_register() checks if you specify proc_fops. If you don't, it will set default 
 * file operations for procfs. Default operations calls your proc_read and proc_write. So, if you specify proc_fops 
 * by yourself, proc_read and proc_write members will not be called.
 *
 * In linux-3.10 there aren't such things as write_proc_t and read_proc_t. proc_dir_entry has no members read_proc 
 * and write_proc. Instead, only proc_fops is used.
 */

DEFINE_MUTEX(rtclock);
void read_rtc_time(int *hr,int *min,int *sec){
	
	pr_info("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%s: invoked\n",__func__);
	_READ_RTC(*hr ,HOUR);
	_READ_RTC(*min,MINT);
	_READ_RTC(*sec,SECD);

}

void write_rtc_time(int hr,int min,int sec){

        _WRITE_RTC(hr ,HOUR);
        _WRITE_RTC(min,MINT);
        _WRITE_RTC(sec,SECD);

}


void read_rtc_date(int *date,int *mon,int *year){

        _READ_RTC(*date,DATE);
        _READ_RTC(*mon ,MONT);
        _READ_RTC(*year,YEAR);

}

void write_rtc_date(int date,int mon,int year){

        _WRITE_RTC(date,DATE);
        _WRITE_RTC(mon ,MONT);
        _WRITE_RTC(year,YEAR);

}

int RTC_open(struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__func__);
	return 0;

}

ssize_t read_time(struct file *fl, char __user *buf, size_t sz, loff_t *loff)
{	
	int hr,min,sec;
	int len;
	
//	if(*loff==-1)
//		return 0;
	if(mutex_is_locked(&rtclock))
				return -EBUSY;
	mutex_lock_interruptible(&rtclock);
	read_rtc_time(&hr,&min,&sec);
	len = sprintf(buf,"time: %x:%02x:%02x\n",hr,min,sec);
	*loff+=len;
	pr_info("read_time: %s, %x:%02x:%02x\n",buf,hr,min,sec);
	//len = sprintf(buf,"time: %x:%02x:%02x\b\b\b\b\b\b\b\b\b\b\b\b\b       \b\b\b\b\b\b\b\b\b\b\b\b\b",hr,min,sec);
	mutex_unlock(&rtclock);

	return len;

}

        
ssize_t write_time(struct file *fl, const char __user *buffer, size_t sz, loff_t *loff)
{

			//we are unable to write directly,coz no echo and vi editor are unable to write the 
			// vi "/proc/RTC/rw_time" file, so from test_application only we can interact with RTC
        int hr,min,sec;
        int len;

        if(mutex_is_locked(&rtclock))
                              return -EBUSY;
        mutex_lock_interruptible(&rtclock);
        len = sscanf(buffer,"time: %x:%x:%x",&hr,&min,&sec);
	pr_info("write_time: %s, %x:%02x:%02x\n",buffer,hr,min,sec);
        write_rtc_time(hr,min,sec);
        mutex_unlock(&rtclock);

        return len;

}


ssize_t read_date(struct file *fl, char __user *buf, size_t sz, loff_t *loff)
{	
        int date,mon,year;
	int len;

	if(mutex_is_locked(&rtclock))
                                return -EBUSY;
	mutex_lock_interruptible(&rtclock);
        read_rtc_date(&date,&mon,&year);
	len = sprintf(buf,"date: %x/%02x/20%02x\n",date,mon,year);
	mutex_unlock(&rtclock);

        return len;

}

ssize_t write_date(struct file *fl, const char __user *buffer, size_t sz, loff_t *loff)
{
			//we are unable to write directly,coz no echo and vi editor are unable to write the 
                        // vi "/proc/RTC/rw_time" file, so from test_application only we can interact with RTC

        int date,mon,year;
        int len;

        if(mutex_is_locked(&rtclock))
                              return -EBUSY;
        mutex_lock_interruptible(&rtclock);
        len = sscanf(buffer,"date: %x/%02x/%02x",&date,&mon,&year);
        pr_info("write_date: %s, %x/%02x/%02x\n",buffer,date,mon,year);
        write_rtc_date(date,mon,year);
        mutex_unlock(&rtclock);

        return len;

}

int RTC_release(struct inode *in, struct file *dfl){

	pr_info("%s: Invoked\n",__func__);
	return SUCCESS;

}

#define DIRNAME 		"RTC"
#define PROC_RW_DATE_ENTRY	"rw_date"
#define PROC_RW_TIME_ENTRY	"rw_time"

struct proc_dir_entry *pdep_parent;				/* RTC*/
struct proc_dir_entry *Time,*Date;				/* entities under RD_RTC & WR_RTC */

struct file_operations timefops={.owner=THIS_MODULE,
				 .open=RTC_open,
				 .read=read_time,
				 .write=write_time,
				 .release=RTC_release
				},
			datefops={.owner=THIS_MODULE,
				  .open=RTC_open,
                                  .read=read_date,
                                  .write=write_date,
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
	Date = proc_create(PROC_RW_DATE_ENTRY,0666,pdep_parent,&datefops);
                if(!Date){
                        pr_info("failed to create proc_entry\n");
                        return FAILURE;
                        }
	return SUCCESS;
	
}


static int __init rd_rtc_register(void){


#ifdef USE
	pr_info("%s: invoked\n",__FUNCTION__);
	return create_proc_entry_function();
#endif
	pr_info("%s: Kernel version is not supported\n",__FUNCTION__);
	return FAILURE;
}

static void __exit rd_rtc_deregister(void){

	pr_info("%s: invoked\n",__FUNCTION__);

	remove_proc_entry(PROC_RW_TIME_ENTRY,pdep_parent);/*entities*/
	remove_proc_entry(PROC_RW_DATE_ENTRY,pdep_parent);

	remove_proc_entry(DIRNAME,NULL);/*MAIN DIR*/

}

module_init(rd_rtc_register);
module_exit(rd_rtc_deregister);

MODULE_LICENSE("GPL");
