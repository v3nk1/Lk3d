#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>

#include<asm/uaccess.h>

#include"../MACROS.h"

#define FAILURE -1
#define CHRDRV_NAME "/dev/rdrtc"  //this entry will appears only in cat /proc/devices

dev_t devid;
struct cdev *cdevp;

void find_day(int tmp,char *pop){

					switch(tmp){
						case 1:
							pop[0] = 'S';
							pop[1] = 'u';
							pop[2] = 'n';
							pop[3] = ' ';
							break;
						case 2:	
							pop[0] = 'M';
							pop[1] = 'o';
							pop[2] = 'n';
							pop[3] = ' ';
							break;
						case 3:	
							pop[0] = 'T';
							pop[1] = 'u';
							pop[2] = 'e';
							pop[3] = ' ';
							break;
						case 4:	
							pop[0] = 'W';
							pop[1] = 'e';
							pop[2] = 'd';
							pop[3] = ' ';
							break;
						case 5:	
							pop[0] = 'T';
							pop[1] = 'h';
							pop[2] = 'u';
							pop[3] = ' ';
							break;
						case 6:	
							pop[0] = 'F';
							pop[1] = 'r';
							pop[2] = 'i';
							pop[3] = ' ';
							break;
						case 7:	
							pop[0] = 'S';
							pop[1] = 'a';
							pop[2] = 't';
							pop[3] = ' ';
							break;
						}
}

void find_month(int tmp,char *pop){

					switch(tmp){
						case 0x01:
							pop[4] = 'J';
							pop[5] = 'a';
							pop[6] = 'n';
							pop[7] = ' ';
							break;
						case 0x02:	
							pop[4] = 'F';
							pop[5] = 'e';
							pop[6] = 'b';
							pop[7] = ' ';
							break;
						case 0x03:	
							pop[4] = 'M';
							pop[5] = 'a';
							pop[6] = 'r';
							pop[7] = ' ';
							break;
						case 0x04:	
							pop[4] = 'A';
							pop[5] = 'p';
							pop[6] = 'r';
							pop[7] = ' ';
							break;
						case 0x05:	
							pop[4] = 'M';
							pop[5] = 'a';
							pop[6] = 'y';
							pop[7] = ' ';
							break;
						case 0x06:	
							pop[4] = 'J';
							pop[5] = 'u';
							pop[6] = 'n';
							pop[7] = ' ';
							break;
						case 0x07:	
							pop[4] = 'J';
							pop[5] = 'u';
							pop[6] = 'l';
							pop[7] = ' ';
							break;
						case 0x08:	
							pop[4] = 'A';
							pop[5] = 'u';
							pop[6] = 'g';
							pop[7] = ' ';
							break;
						case 0x09:	
							pop[4] = 'S';
							pop[5] = 'e';
							pop[6] = 'p';
							pop[7] = ' ';
							break;
						case 0x10:	
							pop[4] = 'O';
							pop[5] = 'c';
							pop[6] = 't';
							pop[7] = ' ';
							break;
						case 0x11:	
							pop[4] = 'N';
							pop[5] = 'o';
							pop[6] = 'v';
							pop[7] = ' ';
							break;
						case 0x12:	
							pop[4] = 'D';
							pop[5] = 'e';
							pop[6] = 'c';
							pop[7] = ' ';
							break;
						}
}


char cho;
void app_handler(char *pop){
	
	char *first = pop;
	char *second = pop+1;
	unsigned int tmp;
	switch(cho){
                        case 'D':	
					__RD_DATE(tmp);
					*first=((tmp & 0xf0)>>4)+48;
					*second=(tmp & 0x0f)+48;
					pop[2]='\0';
					return;
					
                        case 'M':       
					__RD_MON(tmp);
					*first=((tmp & 0xf0)>>4)+48;
                                        *second=((tmp & 0x0f))+48;
					pop[2]='\0';
					return;

                        case 'Y':       
					__RD_YEAR(tmp);
					*first=((tmp & 0xf0)>>4)+48;
                                        *second=(tmp & 0x0f)+48;
					pop[2]='\0';
                                        return;

                        case 'h':  
				        __RD_HOUR(tmp);
					*first=((tmp & 0xf0)>>4)+48;
                                        *second=(tmp & 0x0f)+48;
					pop[2]='\0';
                                        return;

                        case 'm':       
					__RD_MIN(tmp);
					*first=((tmp & 0xf0)>>4)+48;
                                        *second=(tmp & 0x0f)+48;
					pop[2]='\0';
                                        return;

                        case 's':      
					 __RD_SEC(tmp);
					*first=((tmp & 0xf0)>>4)+48;
                                        *second=(tmp & 0x0f)+48;
					pop[2]='\0';
	                                return;

                        case 't':       __RD_HOUR(tmp);
                                       /* 24 hours formate
					pop[0]=((tmp & 0xf0)>>4)+48;
                                        pop[1]=(tmp & 0x0f)+48;
					*/
					//AM:PM formate
					if(tmp>=0x12) {
						if(tmp>0x12) tmp-=0x12;//try to check this statement in calc(put in hex formate);
							if(tmp >0x7 && tmp<0x10) tmp-=0x6;
							pop[8]=' ';pop[9]='P';pop[10]='M';pop[11]='\0';}
					else {pop[8]=' ';pop[9]='A';pop[10]='M';pop[11]='\0';}

                                        pop[0]=((tmp & 0xf0)>>4)+48;
						if(pop[0]=='0') pop[0]=' ';
	                                pop[1]=(tmp & 0x0f)+48;

					pop[2]=':';
					
					__RD_MIN(tmp);
                                        pop[3]=((tmp & 0xf0)>>4)+48;
                                        pop[4]=(tmp & 0x0f)+48;
					pop[5]=':';
					
					__RD_SEC(tmp);
                                        pop[6]=((tmp & 0xf0)>>4)+48;
                                        pop[7]=(tmp & 0x0f)+48;
					
					return;

                        case 'd':       __RD_DAY(tmp);
					find_day(tmp,pop);
					__RD_MON(tmp);
					find_month(tmp,pop);
					__RD_DATE(tmp);
					pop[8]=((tmp & 0xf0)>>4)+48;
                                        pop[9]=(tmp & 0x0f)+48;
                                        __RD_YEAR(tmp);
					pop[10]=' ';
					pop[11]='2';
					pop[12]='0';
                                        pop[13]=((tmp & 0xf0)>>4)+48;
                                        pop[14]=(tmp & 0x0f)+48;
					pop[15]='\0';
					return;

                        case 'T':       __RD_DAY(tmp);
                                        find_day(tmp,pop);
                                        __RD_MON(tmp);
                                        find_month(tmp,pop);
                                        __RD_DATE(tmp);
                                        pop[8]=((tmp & 0xf0)>>4)+48;
                                        pop[9]=(tmp & 0x0f)+48;
                                        __RD_YEAR(tmp);
					pop[10]=' ';
                                        pop[11]='2';
                                        pop[12]='0';
                                        pop[13]=((tmp & 0xf0)>>4)+48;
                                        pop[14]=(tmp & 0x0f)+48;
					pop[15]=' ';
					pop[16]=' ';

					 __RD_HOUR(tmp);
                                       /* 24 hours formate
                                        pop[16]=((tmp & 0xf0)>>4)+48;
                                        pop[17]=(tmp & 0x0f)+48;
                                        */
                                        //AM:PM formate
                                        if(tmp>=0x12) {
						if(tmp>0x12) tmp-=0x12;//try to check this statement in calc(put in hex formate);
                                                	if(tmp >0x7 && tmp<0x10) tmp-=0x6;
							pop[25]=' ';pop[26]='P';pop[27]='M';pop[28]='\0';}

                                        else {pop[25]=' ';pop[26]='A';pop[27]='M';pop[28]='\0';}

                                        pop[17]=((tmp & 0xf0)>>4)+48;
                                        pop[18]=(tmp & 0x0f)+48;

                                        pop[19]=':';

                                        __RD_MIN(tmp);
                                        pop[20]=((tmp & 0xf0)>>4)+48;
                                        pop[21]=(tmp & 0x0f)+48;
                                        pop[22]=':';

                                        __RD_SEC(tmp);
                                        pop[23]=((tmp & 0xf0)>>4)+48;
                                        pop[24]=(tmp & 0x0f)+48;


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

	int base_minorno = 0;
	pr_info("chrdrv: Registered\n");
	
/*Registering MAJOR and MINOR no's */
	if(alloc_chrdev_region(&devid,base_minorno,1,CHRDRV_NAME)<0){//searchs majorno which is free at that time dymanically and combines it our given minorno and finally populate devid with maj&minor(since it call by reference)
			pr_info("failed to register maj,min no..\n");
			return FAILURE;
			}
	
	pr_info("MAJOR: %d, MINOR: %d\n",MAJOR(devid),MINOR(devid));


/*1st create a class in /sys/VIRTUAL	then

Create a device node for aquired major and minor no.. dynamincally using udev userspace deamon. U can see it in "ls /sys/class/VIRTUAL" */	
	clas = class_create(THIS_MODULE,"VIRTUAL");
	devp = device_create(clas,NULL,devid,NULL,"%s%i","caldev",123); //it will appear in /dev/caldev123

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
