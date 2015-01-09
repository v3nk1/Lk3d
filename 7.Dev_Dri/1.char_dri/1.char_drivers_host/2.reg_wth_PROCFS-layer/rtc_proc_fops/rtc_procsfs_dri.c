/*
 * In this prog we are using vfs layer file_operations structure instead of using procfs abstraction layer funtions
 * So we cannot perform normal file "read/write" using 'cat' command or 'vi editor'/echo. So u must invoke normal read/write api's
 * through test-application only
 * 
 */

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/slab.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/proc_fs.h>
#include<linux/mutex.h>
#include"RTC_HEADER.h"

#define SUCCESS  0
#define FAILURE -1

//#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,10,0)
	
	#define USE

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

	
ssize_t read_time (struct file *filp, char __user *buf, size_t sz, loff_t *off){

	int hr,min,sec;
	int len;
	
	if(mutex_is_locked(&rtclock))
				return -EBUSY;
	mutex_lock_interruptible(&rtclock);
	read_rtc_time(&hr,&min,&sec);
	len = sprintf(buf,"time: %x:%02x:%02x\n",hr,min,sec);
	mutex_unlock(&rtclock);

	return len;

}


ssize_t write_time (struct file *filp, const char __user *buffer, size_t sz, loff_t *off){

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


ssize_t read_date (struct file *filp, char __user *buf, size_t sz, loff_t *off){
	
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

ssize_t write_date (struct file *filp, const char __user *buffer, size_t sz, loff_t *off){

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


#define DIRNAME 		"RTC"
#define PROC_RW_DATE_ENTRY	"rw_date"
#define PROC_RW_TIME_ENTRY	"rw_time"

struct proc_dir_entry *pdep_parent;				/* RTC*/
struct proc_dir_entry *Time,*Date;				/* entities under RD_RTC & WR_RTC */

struct file_operations time_fops = {
					.owner = THIS_MODULE,
					.read = read_time,
					.write = write_time
				};

struct file_operations date_fops = {
					.owner = THIS_MODULE,
					.read = read_date,
					.write = write_date
				};

int create_proc_entry_function(void){
	
	pdep_parent = proc_mkdir(DIRNAME,NULL);			/* RTC*/
		if(!pdep_parent){
			pr_info("failed to create directory\n");
			return FAILURE;
			}

	Time = create_proc_entry(PROC_RW_TIME_ENTRY,0666,pdep_parent);
		if(!Time){
			pr_info("failed to create proc_entry\n");
			return FAILURE;
			}
	Date = create_proc_entry(PROC_RW_DATE_ENTRY,0666,pdep_parent);
                if(!Date){
                        pr_info("failed to create proc_entry\n");
                        return FAILURE;
                        }
	
	Time->proc_fops = &time_fops;

	Date->proc_fops = &date_fops;
	
	return SUCCESS;
	
}

#endif

static int __init rd_rtc_register(void){

	pr_info("%s: invoked\n",__FUNCTION__);
#ifdef USE
	return create_proc_entry_function();
#endif
	pr_info("Kernel version doesnt support\n");
	return FAILURE;
}

static void __exit rd_rtc_deregister(void){

	pr_info("%s: invoked\n",__FUNCTION__);

#ifdef USE
	remove_proc_entry(PROC_RW_TIME_ENTRY,pdep_parent);/*entities*/
	remove_proc_entry(PROC_RW_DATE_ENTRY,pdep_parent);

	remove_proc_entry(DIRNAME,NULL);/*MAIN DIR*/
#endif

}

module_init(rd_rtc_register);
module_exit(rd_rtc_deregister);

MODULE_LICENSE("GPL");
