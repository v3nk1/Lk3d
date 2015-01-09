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

/*checking current Kernel version*/
#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,10,0)

	#define USE 
		/* If the version supports then i am defining a Macro USE, i will check it in init_module, 
		 * if defined then only i continue other will return FAILURE 
		 */
	
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


DEFINE_MUTEX(rdtime);

int read_time(char *page, char **start, off_t off,
                          int count, int *eof, void *data){
	
	int hr,min,sec;
	int len;
	
	if(mutex_is_locked(&rdtime))
				return -EBUSY;
	mutex_lock_interruptible(&rdtime);
	read_rtc_time(&hr,&min,&sec);
	len = sprintf(page,"time: %x:%02x:%02x\n",hr,min,sec);
	mutex_unlock(&rdtime);

	return len;

}

DEFINE_MUTEX(wrtime);

int write_time(struct file *file, const char __user *buffer,
                           unsigned long count, void *data){

        int hr,min,sec;
        int len;

        if(mutex_is_locked(&wrtime))
                              return -EBUSY;
        mutex_lock_interruptible(&wrtime);
        len = sscanf(buffer,"time: %x:%x:%x",&hr,&min,&sec);
	pr_info("write_time: %s, %x:%02x:%02x\n",buffer,hr,min,sec);
        write_rtc_time(hr,min,sec);
        mutex_unlock(&wrtime);

        return len;

}


DEFINE_MUTEX(rddate);
int read_date(char *page, char **start, off_t off,
                          int count, int *eof, void *data){
	
        int date,mon,year;
	int len;

	if(mutex_is_locked(&rddate))
                                return -EBUSY;
	mutex_lock_interruptible(&rddate);
        read_rtc_date(&date,&mon,&year);
	len = sprintf(page,"date: %x/%02x/20%02x\n",date,mon,year);
	mutex_unlock(&rddate);

        return len;

}

DEFINE_MUTEX(wrdate);
int write_date(struct file *file, const char __user *buffer,
                           unsigned long count, void *data){

        int date,mon,year;
        int len;

        if(mutex_is_locked(&wrdate))
                              return -EBUSY;
        mutex_lock_interruptible(&wrdate);
        len = sscanf(buffer,"date: %x/%02x/%02x",&date,&mon,&year);
        pr_info("write_date: %s, %x/%02x/%02x\n",buffer,date,mon,year);
        write_rtc_date(date,mon,year);
        mutex_unlock(&wrdate);

        return len;

}


#define DIRNAME 		"RTC"
#define SUBDIR_RD		"RD_RTC"
#define SUBDIR_WR		"WR_RTC"

#define PROC_RD_DATE_ENTRY	"read_date"
#define PROC_WR_DATE_ENTRY	"write_date"
#define PROC_RD_TIME_ENTRY	"read_time"
#define PROC_WR_TIME_ENTRY      "write_time"

struct proc_dir_entry *pdep_parent;			  /* RTC*/
struct proc_dir_entry *pdep_sdir_rd,*pdep_sdir_wr;  	  /* sub parent (RD_RTC & WR_RTC) */
struct proc_dir_entry *rd_Time,*rd_Date,*wr_Time,*wr_Date;/* entities under RD_RTC & WR_RTC */

int create_proc_entry_function(void){
	
	pdep_parent = proc_mkdir(DIRNAME,NULL);					/* RTC*/
		if(!pdep_parent){
			pr_info("failed to create directory\n");
			return FAILURE;
			}

	pdep_sdir_rd = proc_mkdir(SUBDIR_RD,pdep_parent);			/* RD_RTC: sub directry to RTC */
		if(!pdep_sdir_rd){
			pr_info("failed to create directory\n");
                        return FAILURE;
                        }
	pdep_sdir_wr = proc_mkdir(SUBDIR_WR,pdep_parent);		       	/* WR_RTC: sub directry to RTC */
                if(!pdep_sdir_wr){
                        pr_info("failed to create directory\n");
                        return FAILURE;
                        }

	rd_Time = create_proc_entry(PROC_RD_TIME_ENTRY,0666,pdep_sdir_rd);
		if(!rd_Time){
			pr_info("failed to create proc_entry\n");
			return FAILURE;
			}
	rd_Date = create_proc_entry(PROC_RD_DATE_ENTRY,0,pdep_sdir_rd);
                if(!rd_Date){
                        pr_info("failed to create proc_entry\n");
                        return FAILURE;
                        }
	
	wr_Time = create_proc_entry(PROC_WR_TIME_ENTRY,0666,pdep_sdir_wr);
						//here the permissions must be 0666, rw-rw-rw permissions
						//Otherwise write will successful but nodata will be written
						//Actually we shud check the permissions
                if(!wr_Time){
                        pr_info("failed to create proc_entry\n");
                        return FAILURE;
                        }
        wr_Date = create_proc_entry(PROC_WR_DATE_ENTRY,0666,pdep_sdir_wr);
                if(!wr_Date){   
                        pr_info("failed to create proc_entry\n");
                        return FAILURE;
                        }
	
	rd_Time->read_proc = read_time;
	wr_Time->write_proc = write_time;
	//rd_Time->write_proc = write_time;	 then we can write using that rd_Time file also

	rd_Date->read_proc = read_date;	
	wr_Date->write_proc = write_date;
	
	return SUCCESS;
	
}

#endif

static int __init rd_rtc_register(void){
	
	pr_info("%s: invoked\n",__FUNCTION__);
#ifdef USE	/*checking the version supports or not using a macro USE */
	return create_proc_entry_function();
#endif 
	pr_info("Kernel version hasn't supported\n");
       
 return FAILURE; //If u return FAIL then module cannot inserted.
	
}

static void __exit rd_rtc_deregister(void){

	pr_info("%s: invoked\n",__FUNCTION__);
#ifdef USE
	remove_proc_entry(PROC_RD_TIME_ENTRY,pdep_sdir_rd);/*entities*/
	remove_proc_entry(PROC_RD_DATE_ENTRY,pdep_sdir_rd);
	remove_proc_entry(PROC_WR_TIME_ENTRY,pdep_sdir_wr);
	remove_proc_entry(PROC_WR_DATE_ENTRY,pdep_sdir_wr);

	remove_proc_entry(SUBDIR_RD,pdep_parent);/*SUBDIRS*/
	remove_proc_entry(SUBDIR_WR,pdep_parent);
	
	remove_proc_entry(DIRNAME,NULL);/*MAIN DIR*/
#endif
}

module_init(rd_rtc_register);
module_exit(rd_rtc_deregister);

MODULE_LICENSE("GPL");

