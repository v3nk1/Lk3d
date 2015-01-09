//sprintf defaultly put '\0' at end of buffer, keep it mind

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>

#include<asm/uaccess.h>

#include"../MACROS.h"

#define FAILURE -1
#define CHRDRV_NAME "/dev/rdrtc"  //this entry will appears in cat /proc/devices

dev_t devid;
struct cdev *cdevp;

void find_day(int tmp,char *pop){

					switch(tmp){
						case 1:
							sprintf(pop,"Sun ");
							break;
						case 2:	
							sprintf(pop,"Mon ");
							break;
						case 3:	
							sprintf(pop,"Tue ");
							break;
						case 4:	
							sprintf(pop,"Wed ");
							break;
						case 5:	
							sprintf(pop,"Thu ");
							break;
						case 6:	
							sprintf(pop,"Fri ");
							break;
						case 7:	
							sprintf(pop,"Sat ");
							break;
						}
}

void find_month(int tmp,char *pop){
	int _i = 4;
					switch(tmp){
						case 0x01:
							sprintf(pop+_i,"Jan ");
							break;
						case 0x02:	
							sprintf(pop+_i,"Feb ");
							break;
						case 0x03:	
							sprintf(pop+_i,"Mar ");
							break;
						case 0x04:	
							sprintf(pop+_i,"Apr ");
							break;
						case 0x05:	
							sprintf(pop+_i,"May ");
							break;
						case 0x06:	
							sprintf(pop+_i,"Jun ");
							break;
						case 0x07:	
							sprintf(pop+_i,"Jul ");
							break;
						case 0x08:	
							sprintf(pop+_i,"Aug ");
							break;
						case 0x09:	
							sprintf(pop+_i,"Sep ");
							break;
						case 0x10:	
							sprintf(pop+_i,"Oct ");
							break;
						case 0x11:	
							sprintf(pop+_i,"Nov ");
							break;
						case 0x12:	
							sprintf(pop+_i,"Dec ");
							break;
						}
}


char cho;
void app_handler(char *pop){
	
	unsigned int tmp;
	switch(cho){
                        case 't':       __RD_HOUR(tmp);
                                       /* 24 hours formate
					pop[0]=((tmp & 0xf0)>>4)+48;
                                        pop[1]=(tmp & 0x0f)+48;
					*/
					//AM:PM formate
					if(tmp>=0x12) {
						if(tmp>0x12) tmp-=0x12;//try to check this statement in calc(put in hex formate);
							if(tmp >0x7 && tmp<0x10) tmp-=0x6;
							sprintf(pop+8," PM");
							}
					else {sprintf(pop+8," AM");}
				
					sprintf(pop,"%02x:",tmp); //%02x is compulsary other wise cause problem becoz if tmp								is lessthan 10 then it only use only one char instead of 2 char

					__RD_MIN(tmp);
					sprintf(pop+3,"%02x:",tmp);
					
					__RD_SEC(tmp);
					sprintf(pop+6,"%02x",tmp);
					pop[8]=' ';//to replace the null with space since %s shud print total naa..
					return;

                        case 'd':       __RD_DAY(tmp);
					find_day(tmp,pop);
					__RD_MON(tmp);
					find_month(tmp,pop);
					__RD_DATE(tmp);
					sprintf(pop+8,"%x",tmp);
                                        __RD_YEAR(tmp);
					sprintf(pop+10," 20%02x",tmp);
					return;

                        case 'T':       
					__RD_DAY(tmp);
                                        find_day(tmp,pop);
                                        __RD_MON(tmp);
                                        find_month(tmp,pop);
                                        __RD_DATE(tmp);
                                        sprintf(pop+8,"%02x",tmp);
                                        __RD_YEAR(tmp);
                                        sprintf(pop+10," 20%02x  ",tmp);

					 __RD_HOUR(tmp);
                                       /* 24 hours formate
                                        pop[16]=((tmp & 0xf0)>>4)+48;
                                        pop[17]=(tmp & 0x0f)+48;
                                        */
                                        //AM:PM formate
                                        if(tmp>=0x12) {
						if(tmp>0x12) tmp-=0x12;//try to check this statement in calc(put in hex formate);
                                                	if(tmp >0x7 && tmp<0x10) tmp-=0x6;
							sprintf(pop+25," PM");
							}

                                        else {sprintf(pop+25," AM");}//sprintf automatically places \0 at end

					sprintf(pop+17,"%02x:",tmp);

                                        __RD_MIN(tmp);
					sprintf(pop+20,"%02x:",tmp);

                                        __RD_SEC(tmp);
					sprintf(pop+23,"%02x",tmp);
					pop[25]=' ';//replacing sprintf created null at pop[25] to ' '
					return;
			
		}

}

int cdev_open (struct inode *in, struct file *fl){
	
	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;	

}

int cdev_close (struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;

}

ssize_t cdev_read (struct file *fl, char __user *buf, size_t sz, loff_t *lf){

	char tmp[100];
	app_handler(tmp);
	pr_info("ccccccccccc: %s\n",tmp);
	copy_to_user(buf,tmp,sz);
	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;

}

ssize_t cdev_write (struct file *fl, const char __user *buf, size_t sz, loff_t *lf){
	
	char devwr_msg[100];
	//if(strlen_user(buf)!=1) return -1;
	cho = *buf;
	pr_info("%s: Invoked\n",__FUNCTION__);
	copy_from_user(devwr_msg,buf,sizeof(devwr_msg));
	pr_info("devwrmsg: %s\n",devwr_msg);
	return 0;

}

/*loff_t misc_lseek(struct file *fl, loff_t off, int whence){

        if(off<0)
                 return -EOVERFLOW;

        switch(whence){
                case SEEK_SET:
                                fl->f_pos = off;
                                break;
                case SEEK_CUR:
                                fl->f_pos += off;
                                break;

                case SEEK_END:
                                fl->f_pos = KBUF_MAX + off;
                                                //Dont use sizeof instead KBUF_MAX
                                break;
                default:
                                pr_info("%s: Invalid Whence\n",__FUNCTION__);
                                return -EINVAL;
                }

        return (off > KBUF_MAX) ?  off=KBUF_MAX : off;

}
*/

struct file_operations fops={
				.owner 	= THIS_MODULE,
				.open 	= cdev_open,
				.read 	= cdev_read,
				.write	= cdev_write,
				.release= cdev_close
			
			};

struct device *devp;
struct class *clas;

static int __init chrdrv_init(void){

	int minorno = 0;
	pr_info("chrdrv: Registered\n");
	
/*Registering MAJOR and MINOR no's */
	if(alloc_chrdev_region(&devid,minorno,1,CHRDRV_NAME)<0){//searchs majorno which is free at that time dymanically and combines it our given minorno and finally populate devid with maj&minor(since it call by reference)
			pr_info("failed to register maj,min no..\n");
			return FAILURE;
			}
	
	pr_info("MAJOR: %d, MINOR: %d\n",MAJOR(devid),MINOR(devid));


/*1st create a class in /sys/VIRTUAL	then

Create a device node for aquired major and minor no.. dynamincally using udev userspace deamon. U can see it in "ls /sys/class/VIRTUAL" */	
	clas = class_create(THIS_MODULE,"VIRTUAL");
	devp = device_create(clas,NULL,devid,NULL,"%s%i","caldev",123);

/* Registering our routines with VFS	*/
	cdevp = cdev_alloc();
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
