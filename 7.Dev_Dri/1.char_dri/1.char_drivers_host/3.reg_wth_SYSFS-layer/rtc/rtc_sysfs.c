#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

#include "RTC_HEADER.h"

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

/* read routine for time entry */
static ssize_t tm_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf)
{
	int hr,min,sec;
	int len;

	pr_info("%s: Invoked\n",__func__);
        if(mutex_is_locked(&rtclock))
                                return -EBUSY;
        mutex_lock_interruptible(&rtclock);
	read_rtc_time(&hr,&min,&sec);

	//Copying aquired data to "/sys/time" entry
        len=sprintf(buf,"time: %x:%02x:%02x\n",hr,min,sec );
	mutex_unlock(&rtclock);
	return len;
}

/* write routine for time entry */
static ssize_t tm_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count)
{
	int hr,min,sec;
        int len;
	pr_info("%s: Invoked\n",__func__);

        if(mutex_is_locked(&rtclock))
                              return -EBUSY;
        mutex_lock_interruptible(&rtclock);

	//Aquiring/reading data from "/sys/time" entry
        len = sscanf(buf,"time: %x:%x:%x",&hr,&min,&sec);
        pr_info("%s: %s, %x:%02x:%02x\n",__func__,buf,hr,min,sec);
        write_rtc_time(hr,min,sec);
        mutex_unlock(&rtclock);

        return count/*len*/;

}

/* read routine for date entry */
static ssize_t dt_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	int date,mon,year;
	int len;
	pr_info("%s: Invoked\n",__func__);

        if(mutex_is_locked(&rtclock))
                                return -EBUSY;
        mutex_lock_interruptible(&rtclock);
	read_rtc_date(&date,&mon,&year);
	len=sprintf(buf,"date: %x/%02x/20%02x\n",date,mon,year);
        pr_info("%s: %s, %x/%02x/%02x\n",__func__,buf,date,mon,year);
	mutex_unlock(&rtclock);
	
	return len;
}

/* write routine for date entry */
static ssize_t dt_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count)
{
	int date,mon,year;
        int len;
	pr_info("%s: Invoked\n",__func__);

        if(mutex_is_locked(&rtclock))
                              return -EBUSY;
        mutex_lock_interruptible(&rtclock);
        len = sscanf(buf,"date: %x/%02x/%02x",&date,&mon,&year);
        pr_info("%s: %s, %x/%02x/%02x\n",__func__,buf,date,mon,year);
        write_rtc_date(date,mon,year);
        mutex_unlock(&rtclock);

        return len;
}

/* Linking routines to particular entry */
/* Use __ATTR family to ensure that naming convention */
static struct kobj_attribute tm_attribute =
	__ATTR(time, 0666, tm_show, tm_store);
static struct kobj_attribute dt_attribute =
	__ATTR(date, 0666, dt_show, dt_store);

/* Constructing suffice environmet for I/O */
static struct attribute *attrs[] = {
        &tm_attribute.attr,
	&dt_attribute.attr,
        NULL,   /* need to NULL terminate the list of attributes */
};
static struct attribute_group attr_group = {
        .attrs = attrs,
};

static struct kobject *rtc_kobj;

static int __init rtc_init(void)
{
	int retval;

	pr_info("%s: Invoked\n",__func__);

	/*
	 * kobject_create_and_add - create a struct kobject dynamically and register it with sysfs
 	 */
	rtc_kobj = kobject_create_and_add("rtc_kobj",NULL /*kernel_kobj*/);
					/*
					 * If you pass kernel_kobj or NULL as 2nd argument entry will
					 * created in /sys/kernel/<kobj-name> or /sys/<kobj-name>
					 */
	if (!rtc_kobj)
		return -ENOMEM;
//	kboject_create_and_add("subrtc",rtc_kobj);
	/* Create the files associated with this kobject */
	retval = sysfs_create_group(rtc_kobj, &attr_group);
	if (retval)
		kobject_put(rtc_kobj);

	return retval;
}

static void __exit rtc_exit(void)
{
	pr_info("%s: Invoked\n",__func__);
	/* Removing sysfs entry */
	kobject_put(rtc_kobj);
}

EXPORT_SYMBOL_GPL(rtc_kobj);
	/*
	 * For any other modules use this variable inorder to create
	 * a sub directory in /sys/rtc_kobj, So we are exporting this symbol as
	 * world usable.
	 */
module_init(rtc_init);
module_exit(rtc_exit);

MODULE_LICENSE("GPL");
