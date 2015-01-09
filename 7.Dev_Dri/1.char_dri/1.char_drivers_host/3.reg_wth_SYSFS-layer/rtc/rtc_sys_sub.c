#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

extern struct kobject *rtc_kobj;

static struct kobj_attribute tm_attribute =
	__ATTR(time, 0666,NULL,NULL);
static struct kobj_attribute dt_attribute =
	__ATTR(date, 0666, NULL, NULL);

/* Constructing suffice environmet for I/O */
static struct attribute *attrs[] = {
        &tm_attribute.attr,
	&dt_attribute.attr,
        NULL,   /* need to NULL terminate the list of attributes */
};
static struct attribute_group attr_group = {
        .attrs = attrs,
};

static struct kobject *sub_kobj;

static int __init rtc_init(void)
{
	int retval;

	pr_info("%s: Invoked\n",__func__);

	/*
	 * kobject_create_and_add - create a struct kobject dynamically and register it with sysfs
 	 */
	sub_kobj = kobject_create_and_add("rtc_sub",rtc_kobj);
					/*
					 * If you pass kernel_kobj or NULL as 2nd argument entry will
					 * created in /sys/kernel/<kobj-name> or /sys/<kobj-name>
					 */
	if (!sub_kobj)
		return -ENOMEM;
//	kboject_create_and_add("subrtc",rtc_kobj);
	/* Create the files associated with this kobject */
	retval = sysfs_create_group(sub_kobj, &attr_group);
	if (retval)
		kobject_put(sub_kobj);

	return retval;
}

static void __exit rtc_exit(void)
{
	pr_info("%s: Invoked\n",__func__);
	/* Removing sysfs entry */
	kobject_put(sub_kobj);
}
module_init(rtc_init);
module_exit(rtc_exit);

MODULE_LICENSE("GPL");
