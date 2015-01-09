
//Its same as 1.kmalc_ioctl but here it supports only ioctl, through ioctl u hav to perform read, write operations	To achive it application has to create an instace of our defined structure inorder to send the size and buff base address and return value storage
	//And more over here in this approch to avoid read stravation of applications i used rdlock, wrlock separately
	//Its a concurrent driver.. 

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/path.h>
#include<linux/slab.h>
#include<linux/tty.h>		//for getchar()

#include"ioctl_H.h"

#define DEV_NAME 	"reg_123"
#define BUFA_SIZE 	4096		/*Default size of buffer*/
#define BUFB_SIZE 	4096		/*Default size of buffer*/

#define LOCK 		1
#define ULOCK 		0 

#define SUCCESS 	0
#define FAILURE        -1

//static int __lock; it causess problem since it cannt give access any other minor no.. ever others are free
static char *DEVBUFA,*DEVBUFB;
typedef struct {
		int rdlock;
		int wrlock;
		}lockk_t;

typedef struct dev_info{
		int minor;
		char *buff;
		lockk_t __lock;//device lock to avoid race conditions.
		size_t buff_size;
		size_t size_max; // user can allocate max size of 50000 bytes. otherwise kernel will slow since lack of memory.
	}devinfo_t;	

devinfo_t dev1,dev2;

int open(struct inode *in, struct file *fl){
	
	//devinfo_t dev; dont declare it here, u must declare it as global otherwise in down your are going to store the address of dev but its no more after open post amble executed. Other declare here static
	//for one module one dev is not sufficent,since recent opened data will be present, previous data jump jilani

	pr_info("%s: Invoked\n",__FUNCTION__);
	
	switch(iminor(in)){

			case 0:{
					dev1.minor = 0;
					dev1.buff = DEVBUFA;
					dev1.buff_size = BUFA_SIZE;
					dev1.size_max = 2000000; /*2MB*/
					fl->private_data = &dev1;
				}
				break;

			case 1:{
					dev2.minor = 1;
                	                dev2.buff = DEVBUFB;
					dev2.buff_size = BUFB_SIZE;
					dev2.size_max = 200000;  /*2MB*/
					fl->private_data = &dev2;
				}
				break;

			default:
				pr_info("Invalid minor no\n");
				break;

			}
	

	return SUCCESS;
}

ssize_t read(struct file *fl, char __user *buf,size_t sz, loff_t *off){

	char *pos;
        int ret;
	devinfo_t *devp = fl->private_data;

        /*
         * If u want to performe read operation first u hav to know from which buffer u shud read data.
         * I ment that 2 devices are associated with this driver module.
         */

	if(devp->__lock.rdlock){
			pr_info("Buf-Busy: Other app is writing..\n");
			return FAILURE;
			}

	devp->__lock.wrlock++;//it shud be atomic instruction	//preventing writing while any app reading buffer.

	pr_info("%s: Invoked\n",__FUNCTION__);

       	if(sz<0) return -EINVAL;

	if(sz > devp->buff_size)
               	        sz = devp->buff_size;
       	if(sz+*off > devp->buff_size)
			sz = devp->buff_size-*off;

       	pos = devp->buff + *off;
       	ret = copy_to_user(buf,pos,sz);
       	*off += sz;

	pr_info("off: %llu\n",*off);
	
	devp->__lock.wrlock--;//shud be atomic instruction	//removing write protection..

	return sz-ret;
		
}

size_t write(struct file *fl,const char __user *buf,size_t sz, loff_t *off){

	char *pos;
        int ret;
		
	devinfo_t *devp = fl->private_data;
	pr_info("%s-%lu: Invoked\n",__FUNCTION__,sz);
        /*
         * If u want to performe read operation first u hav to know from which buffer u shud read data.
         * I ment that 2 devices are associated with this driver module.
         */
//	pr_info("wr1: %s\n",buf);

	if(devp->__lock.wrlock /*|| devp->__lock.rdlock*/){
		pr_info("Buf-Busy: %d apps reading, %d apps writing\n",devp->__lock.rdlock,devp->__lock.wrlock);
		return FAILURE;
		}

		devp->__lock.rdlock++;//shud be atomic instruction
		devp->__lock.wrlock++;//shud be atomic instruction
	
	//while(1); Dont give infinite loops it will cause kernel hangup(strucked)..		\
		To demostrate locking i 've given. but within 2 min kernel has hanged.. u cannt come out of this loop.

        if(sz<0) return -EINVAL;

        if(sz > devp->buff_size)
                       sz = devp->buff_size;
        if(sz+*off > devp->buff_size)
                       sz = devp->buff_size-*off;

        pos = devp->buff + *off;
        ret = copy_from_user(pos,buf,sz);
//	pr_info("wr2: %s\n",devp->buff);
        *off += sz;
//	pr_info("BUFA: %s",DEVBUFA);
//	pr_info("BUFB: %s",DEVBUFB);
//	pr_info("off: %llu\n",*off);

	devp->__lock.rdlock--;//shud be atomic instruction
        devp->__lock.wrlock--;//shud be atomic instruction

	return sz-ret;
}

loff_t lseek(struct file *fl, loff_t off, int whence){

	devinfo_t *devp = fl->private_data;
	pr_info("%s: Invoked\n",__FUNCTION__);
	
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
				fl->f_pos = devp->buff_size + off;
                                break;
                default:
                                pr_info("%s: Invalid Whence\n",__FUNCTION__);
                                return -EINVAL;
                }

//	pr_info("off: %llu \n",fl->f_pos);
        return (fl->f_pos > devp->buff_size) ?  fl->f_pos=devp->buff_size : fl->f_pos;

}


	
long unlocked_ioctl(struct file *fl, unsigned int cmd, unsigned long usr_obj){
	
	/*
	 * If u perform read operation then user will pass reference as 3rd argument through which u will send data.
	 */

	devinfo_t *devp = fl->private_data;

	pr_info("%s: Invoked\n",__FUNCTION__);

	if(usr_obj<0)
		  return FAILURE;  
	else if(!usr_obj)
		 return FAILURE;
	

	switch(cmd){

		case GET_SIZE:
				*(int *)usr_obj = devp->buff_size;
				break;

		case SET_SIZE:
				if(usr_obj > devp->size_max)  usr_obj = devp->size_max;

				if(!krealloc(devp->buff,usr_obj,GFP_KERNEL)){
								pr_info("krealloc: Failed\n");
								return FAILURE;
								}
				devp->buff_size = usr_obj;
				break;

		case FLUSH_BUF:/* Flush the buff associated with calling device */
				pr_info("ret: %p\n",memset(devp->buff,'\0',devp->buff_size));
				break;

		case FILL_CHAR:
				memset(devp->buff,usr_obj,devp->buff_size);
                                break;
		case RD     :
				{
				rdwr_t *usr_objp = (rdwr_t *)usr_obj;
				pr_info("case RD: Invoked\n");
				if(_IOC_DIR(cmd) & _IOC_READ)
					if(!access_ok(VERIFY_WRITE,usr_objp->buf,usr_objp->size/*_IOC_SIZE(cmd)*/))
								//if u give _IOC_SIZE if size is -ve then also its 														giving access
							return -EFAULT;
				usr_objp->ret_val = read(fl,usr_objp->buf,usr_objp->size,&fl->f_pos);
				}
				break;

		case WR    :
				{
				rdwr_t *usr_objp = (rdwr_t *)usr_obj;
				//int size = usr_objp->size;
				pr_info("case WR: Invoked\n");
                                if(_IOC_DIR(cmd) & _IOC_WRITE)
                                        if(!access_ok(VERIFY_READ,usr_objp->buf,usr_objp->size/*_IOC_SIZE(cmd)*/))
								//if u give _IOC_SIZE if size is -ve then also its                                                                                                              giving access
                                                        return -EFAULT;
				
                                usr_objp->ret_val = write(fl,usr_objp->buf,usr_objp->size,&fl->f_pos);
                               	pr_info("wret: %d\n",usr_objp->ret_val);
				 }
				break;
		default:
				pr_info("cmd: No such command\n");
				return FAILURE;
		}
	
	return SUCCESS;
}

int release(struct inode *in,struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);
	
	return SUCCESS;

}


struct file_operations fops = {
				.owner = THIS_MODULE,
				.open = open,
				//.read = read,
				//.write = write,
				.release = release,
				.llseek = lseek,
				.unlocked_ioctl = unlocked_ioctl
				};

struct class *cls;
int mjrno,minor = 2;  //Beware of local and global declarations since they shudnt match and shudnt redefined..

int __init init_module(void){

	int i;
	dev_t devid;
	
	pr_info("%s: Loaded\n",__FUNCTION__);
	
	if(!(DEVBUFA = kmalloc(BUFA_SIZE,GFP_KERNEL))){
				pr_info("kmalloc(A): Failed\n");
				return FAILURE;
				}
		memset(DEVBUFA,'\0',BUFA_SIZE);

	if(!(DEVBUFB = kmalloc(BUFB_SIZE,GFP_KERNEL))){
				pr_info("kmalloc(B): Failed\n");
				return FAILURE;
				}
		memset(DEVBUFB,'\0',BUFB_SIZE);


	if((mjrno = register_chrdev(0,DEV_NAME,&fops))<0){ 
			pr_info("register_chrdev: Failed\n");
			return FAILURE;
			}
	pr_info("Major no: %d\n",mjrno);

	cls = class_create(THIS_MODULE,"VCLASS");
	
		if(!cls)
			pr_info("cls: ERROR\n");

	for(i=0;i<minor;i++){
		devid = MKDEV(mjrno,i);
		device_create(cls,NULL,devid,NULL,"old%d",i);
		}
	return SUCCESS;
}

void cleanup_module(void){

	int i;
	dev_t devid;

	kfree(DEVBUFA);
	kfree(DEVBUFB);

	for(i=0;i<minor;i++){
                devid = MKDEV(mjrno,i);
                device_destroy(cls,devid);
                }
	class_destroy(cls);
	unregister_chrdev(mjrno,DEV_NAME);
	
	pr_info("%s: Unloaded\n",__FUNCTION__);

}

MODULE_LICENSE("GPL");
