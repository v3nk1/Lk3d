#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<linux/uaccess.h>

#include"rtc_header.h"
#include"ioctl_header.h"

#define SUCCESS 0
#define FAILURE -1

int rtc_open(struct inode *in,struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);

	return SUCCESS;

}

int rtc_release(struct inode *in,struct file *fl){
	
	pr_info("%s: Invoked\n",__FUNCTION__);

	return SUCCESS;

}

long rtc_ioctl(struct file *fl,unsigned int cmd,unsigned long val){
	
	int tmp;

	switch(cmd){

		case RD_DAY	:
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(DAY,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_MON     :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(MON,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_DATE    :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(DATE,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_YR      :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(YR,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_HOUR    :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(HR,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_MIN     :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(MIN,tmp);
				*(int *)val = tmp;
				break;
				
		case RD_SEC     :     
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,(void *)val,_IOC_SIZE(cmd)))
							return -EFAULT;
				__RD_RTC(SEC,tmp);
				*(int *)val = tmp;
				break;
				

		case WR_DAY     :
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(DAY,val);
				break;
				
		case WR_MON     :   
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(MON,val);
				pr_info("wr.mon\n");
				break;
				
		case WR_DATE    :  
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(DATE,val);
				break;
				
		case WR_YR      :
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(YR,val);
				break;
				
		case WR_HOUR    :
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(HR,val);
				break;
				
		case WR_MIN     :
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(MIN,val);
				break;
				
		case WR_SEC     :
				if(_IOC_DIR(cmd) & _IOC_WRITE)
					if(!access_ok(VERIFY_READ,&val,_IOC_SIZE(cmd)))
						return -EFAULT;
				__WR_RTC(SEC,val);
				break;
				
			
		default		:
				pr_info("switch: No such command\n");
				return FAILURE;
	
	}

return SUCCESS;

}

struct file_operations fops = {

				.owner = THIS_MODULE,
				.open = rtc_open,
				.release = rtc_release,
				.unlocked_ioctl = rtc_ioctl

				};

int majorno;
struct class *cls;
dev_t devid;

int __init init_module(void){

	pr_info("rtc: module inserted\n");
	majorno = register_chrdev(0,"RD_RTC",&fops);
	
	
	cls = class_create(THIS_MODULE,"XYZ");
	devid = MKDEV(majorno,0);
	device_create(cls,NULL,devid,NULL,"rdrtc123");

	return SUCCESS;

}

void __exit cleanup_module(void){

	pr_info("rtc: module removed\n");
	
	device_destroy(cls,devid);
	class_destroy(cls);
	
	unregister_chrdev(majorno,"RD_RTC");

}

MODULE_LICENSE("GPL");
