/*
 * Q. Allocate 2 kernel buffers of 1024 bytes each DEVBUFA, DEVBUFB. Implement a char driver that maps DEVBUFA to 	    /dev/bufa and DEVBUFB to /dev/bufb. Driver shud provide support for read, write operations.
 *    In this module we creating a driver having 2 buffers and supports 2 minor numbers
 */

	/*
	 * In this prog, u cannot use misc since misc registers only one minor no..
	 */


#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/path.h>
#include<linux/slab.h>


#define DEV_NAME "reg_123"
#define BUFA_SIZE 1024
#define BUFB_SIZE 1024

#define LOCK 1
#define ULOCK 0 

#define SUCCESS 0
#define FAILURE -1

static int __lock;
static char *DEVBUFA,*DEVBUFB;

typedef struct dev_info{
		int minor;
		char *buff;
		size_t buff_size;
	}devinfo_t;	

int open(struct inode *in, struct file *fl){

//	int minor;
	devinfo_t dev;

	pr_info("%s: Invoked\n",__FUNCTION__);
	if(__lock)
		return FAILURE;
	__lock = LOCK;
	
	switch(iminor(in)){
			case 0:
				dev.minor = 0;
				dev.buff = DEVBUFA;
				dev.buff_size = BUFA_SIZE;
				break;
			case 1:
				dev.minor = 1;
                                dev.buff = DEVBUFB;
				dev.buff_size = BUFB_SIZE;
				break;
			default:
				pr_info("Invalid minor no\n");
				break;
			}
	
	fl->private_data = &dev;

	return SUCCESS;
}

ssize_t read(struct file *fl, char __user *buf,size_t sz, loff_t *off){

	char *pos;
        int ret;
	devinfo_t *dev = fl->private_data;
        /*
         * If u want to performe read operation first u hav to know from which buffer u shud read data.
         * I ment that 2 devices are associated with this driver module.
         */

	pr_info("%s: Invoked\n",__FUNCTION__);
        if(sz<0) return -EINVAL;

/*        switch(iminor(*fl->f_inode)){

                case 0:
                        if(sz>BUFA_SIZE)
                                        sz = BUFA_SIZE;
                        if(sz+*off > BUFA_SIZE)
                                        sz = BUFA_SIZE-*off;

                        pos = DEVBUFA+*off;
                        ret = copy_to_user(buf,pos,sz);
                        *off += sz;
                        break;
                case 1:
                        if(sz>BUFB_SIZE)
					sz = BUFB_SIZE;
                        if(sz+*off > BUFB_SIZE)
                                        sz = BUFB_SIZE-*off;

                        pos = DEVBUFB+*off;
                        ret = copy_to_user(buf,pos,sz);
                        *off += sz;
                        break;
		default:
			pr_info("read: Invalid minor\n");
			break;	

		}
*/
	if(sz > dev->buff_size)
                       sz = dev->buff_size;
        if(sz+*off > dev->buff_size)
                       sz = dev->buff_size-*off;

        pos = dev->buff + *off;
        ret = copy_to_user(buf,pos,sz);
        *off += sz;

	pr_info("off: %d\n",*off);
	return sz-ret;
}

ssize_t write(struct file *fl,const char __user *buf,size_t sz, loff_t *off){

	char *pos;
        int ret;
	devinfo_t *dev = fl->private_data;
        /*
         * If u want to performe read operation first u hav to know from which buffer u shud read data.
         * I ment that 2 devices are associated with this driver module.
         */
	pr_info("wr: %s\n",buf);
	pr_info("%s: Invoked\n",__FUNCTION__);
        if(sz<0) return -EINVAL;

/*        switch(iminor(*fl->f_inode)){

                case 0:
                        if(sz>BUFA_SIZE)
                                        sz = BUFA_SIZE;
                        if(sz+*off > BUFA_SIZE)
                                        sz = BUFA_SIZE-*off;

                        pos = DEVBUFA+*off;
                        ret = copy_from_user(pos,buf,sz);
                        *off += sz;
                        break;
                case 1:
                        if(sz>BUFB_SIZE)
					sz = BUFA_SIZE;
                        if(sz+*off > BUFB_SIZE)
                                        sz = BUFB_SIZE-*off;

                        pos = DEVBUFB+*off;
                        ret = copy_from_user(pos,buf,sz);
                        *off += sz;
                        break;
		default:
			pr_info("read: Invalid minor\n");
			break;	

		}
*/
        if(sz > dev->buff_size)
                       sz = dev->buff_size;
        if(sz+*off > dev->buff_size)
                       sz = dev->buff_size-*off;

        pos = dev->buff + *off;
        ret = copy_from_user(pos,buf,sz);
	pr_info("wr: %s\n",dev->buff);
        *off += sz;
	pr_info("off: %d\n",*off);
	return sz-ret;
}

loff_t lseek(struct file *fl, loff_t off, int whence){

	devinfo_t *dev = fl->private_data;
	pr_info("%s:off: %llu Invoked\n",__FUNCTION__,fl->f_pos);
	
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
/*				switch(iminor(*fl->f_inode)){
				case 0:
                      		        fl->f_pos = BUFA_SIZE + off;
					break;
				case 1:
					fl->f_pos = BUFB_SIZE + off;
					break;
				}
*/				fl->f_pos = dev->buff_size + off;
                                break;
                default:
                                pr_info("%s: Invalid Whence\n",__FUNCTION__);
                                return -EINVAL;
                }

	pr_info("off: %llu \n",fl->f_pos);
        return (fl->f_pos > dev->buff_size) ?  fl->f_pos=dev->buff_size : fl->f_pos;

}

int release(struct inode *in,struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);
	__lock = ULOCK;
	return SUCCESS;

}

struct file_operations fops = {
				.owner = THIS_MODULE,
				.open = open,
				.read = read,
				.write = write,
				.release = release,
				.llseek = lseek
				};

struct class *cls;
int mjrno,minor = 2;  //Beware of local and global declarations since they shudnt match and shudnt redefined..

int __init init_module(void){

	int i;
	dev_t dev;
	
	pr_info("%s: Loaded\n",__FUNCTION__);
	
	if(!(DEVBUFA = kmalloc(BUFA_SIZE,GFP_KERNEL))) 
				pr_info("kmalloc(A): Failed\n");
	if(!(DEVBUFB = kmalloc(BUFB_SIZE,GFP_KERNEL))) 
				pr_info("kmalloc(B): Failed\n");

	if((mjrno = register_chrdev(0,DEV_NAME,&fops))<0){ 
			pr_info("register_chrdev: Failed\n");
			return FAILURE;
			}
	pr_info("Major no: %d\n",mjrno);

	cls = class_create(THIS_MODULE,"VCLASS");
	
		if(!cls)
			pr_info("cls: ERROR\n");

	for(i=0;i<minor;i++){
		dev = MKDEV(mjrno,i);
		device_create(cls,NULL,dev,NULL,"old%d",i);
		}
	return SUCCESS;
}

void cleanup_module(void){

	int i;
	dev_t dev;

	kfree(DEVBUFA);
	kfree(DEVBUFB);

	for(i=0;i<minor;i++){
                dev = MKDEV(mjrno,i);
                device_destroy(cls,dev);
                }
	class_destroy(cls);
	unregister_chrdev(mjrno,DEV_NAME);
	
	pr_info("%s: Unloaded\n",__FUNCTION__);

}

MODULE_LICENSE("GPL");
