#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/miscdevice.h>

#define LOCK 1
#define ULOCK 0

#define MISC_DEV_NAME "misc_API"
#define KBUF_SIZE 4096
#define KBUF_MAX KBUF_SIZE
#define KBUF_OFF kbuf+*off

static int __lock;

char kbuf[KBUF_SIZE];

int misc_open(struct inode *in, struct file *fl){

	if(__lock) 
		return -1;
	__lock = LOCK;
	pr_info("%s: Invoked\n",__FUNCTION__);
	return 0;

}


loff_t misc_lseek(struct file *fl, loff_t off, int whence){

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
				break;
		default:
				pr_info("%s: Invalid Whence\n",__FUNCTION__);
				return -EINVAL;
		}
		

	return (fl->f_pos > KBUF_MAX) ?  fl->f_pos=KBUF_MAX : fl->f_pos;

}

ssize_t misc_read(struct file *fl, char __user *buf, size_t sz, loff_t *off){
				//at the end of this function the value of *off will be stored in fl->f_pos
	int ret;
	pr_info("%s: Invoked\n",__FUNCTION__);	
	
	if(sz>KBUF_MAX)
			sz = KBUF_MAX;
	if(sz<0)	
			return -EINVAL;
	
//	pr_info("off: %llu  fl->fpos: %llu\n",*off,fl->f_pos);	
	if(*off+sz <= KBUF_MAX-*off){
		ret = copy_to_user(buf,KBUF_OFF,sz);
		//pr_info("off %llu\n",*off);
		pr_info("rd: %s\n",KBUF_OFF);
		*off += sz;
		return sz-ret;
		}
	else{	
		ret = copy_to_user(buf,KBUF_OFF,KBUF_MAX-*off);
		*off = KBUF_MAX;
		return KBUF_MAX-*off;
		}
/*	pr_info("off %llu\n",*off);
	pr_info("fl->off %llu\n",fl->f_pos);//it holds previous *off value
*/	
	return -1;
}

#define EGARB -2
ssize_t misc_write(struct file *fl, const char __user *buf, size_t sz, loff_t *off){

	int ret;
	
	pr_info("%s: Invoked\n",__FUNCTION__);
//	if(sz > strlen_user(buf)) return EGARB;
	if(sz > KBUF_MAX)
			return -EIO;
        if(sz<0)
                        return -EINVAL;

	if(*off+sz <= KBUF_MAX){
		ret = copy_from_user(KBUF_OFF,buf,sz);
		*off += sz;
		pr_info("wr: %s\n",kbuf);
		return sz-ret;
		}

	return -1;
}

int misc_release(struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__FUNCTION__);
	__lock=ULOCK;
	return 0;

	}

struct file_operations fops={
				.owner = THIS_MODULE,
				.llseek = misc_lseek,
				.open  = misc_open,
				.read  = misc_read,
				.write = misc_write,
				.release = misc_release
			};
			
	
struct miscdevice md={//its not allowing md.name =  like initialisation(this not supprtd type of initialization is c99 standard)
			.minor = MISC_DYNAMIC_MINOR,
			.name = MISC_DEV_NAME,
			.fops = &fops
			};

static int __init misc_init(void){

	pr_info("Misc-(%s): loaded\n",MISC_DEV_NAME);
	if(misc_register(&md)){ 
			pr_info("misc_reg: Failed\n");
			return -1;
			}
	return 0;

}

static void __exit misc_cleanup(void){

	misc_deregister(&md);
	pr_info("Misc-(%s): unloaded\n",MISC_DEV_NAME);
	
}

module_init(misc_init);
module_exit(misc_cleanup);


MODULE_LICENSE("GPL");
