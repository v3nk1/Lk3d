/*
 * Q. Allocate 2 kernel buffers of 1024 bytes each DEVBUFA, DEVBUFB. Implement a char driver that maps DEVBUFA to 	    /dev/bufa and DEVBUFB to /dev/bufb. Driver shud provide support for read, write operations.
 *    In this module we creating a driver having 2 buffers and supports 2 minor numbers
 *    This approach is also concurrent driver
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
#include<linux/cdev.h>

#define DEV_NAME "device_buffer"
#define BUFCOUNT 2
#define BUFSIZE 4096		/*Default size of buffer*/

#define SUCCESS 0
#define FAILURE -1

#define FOPS_INIT 		{				\
                                .owner = THIS_MODULE,		\
                                .open = open,			\
                                .read = read,			\
                                .write = write,			\
                                .release = release,		\
                                .llseek = lseek			\
                                }

typedef struct devbuf{
	struct mutex mtx;//device lock to avoid race conditions.
	char *buf;
	size_t buf_size;
	int minor;
	}dbuf_t;

typedef struct devpri{
	dbuf_t dbuf[BUFCOUNT];
	struct cdev cdev;
		/* If you give struct cdev *cdev then u need to do cdev_alloc() */
}dpri_t;

dpri_t *pRiV;

int open(struct inode *in, struct file *fl){
	
	dpri_t *dpri = container_of(in->i_cdev,dpri_t,cdev);
	pr_info("%s: Invoked\n",__FUNCTION__);

	switch(iminor(in)){

			case 0:
					mutex_init(&dpri->dbuf[0].mtx);
					dpri->dbuf[0].minor = 0;
					if(!dpri->dbuf[0].buf)
						dpri->dbuf[0].buf = kmalloc(BUFSIZE,GFP_KERNEL);
					dpri->dbuf[0].buf_size = BUFSIZE;
        				fl->private_data = dpri->dbuf+0;
				break;

			case 1:
					mutex_init(&dpri->dbuf[1].mtx);
                                        dpri->dbuf[1].minor = 1;
					if(!dpri->dbuf[1].buf)
                                        	dpri->dbuf[1].buf = kmalloc(BUFSIZE,GFP_KERNEL);
                                        dpri->dbuf[1].buf_size = BUFSIZE;
        				fl->private_data = dpri->dbuf+1;
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
	dbuf_t *dbuf = fl->private_data;
        /*
         * If u want to performe read operation first u hav to know from which buffer u shud read data.
         * I ment that 2 devices are associated with this driver module.
         */

	pr_info("%s: Invoked\n",__FUNCTION__);
        if(sz<0) return -EINVAL;
	
	mutex_lock_interruptible(&dbuf->mtx);
	if(sz > dbuf->buf_size)
                       sz = dbuf->buf_size;
        if(sz+*off > dbuf->buf_size)
                       sz = dbuf->buf_size-*off;

        pos = dbuf->buf + *off;
        ret = copy_to_user(buf,pos,sz);
        *off += sz;
	pr_info("off: %llu\n",*off);
	
	mutex_unlock(&dbuf->mtx);

	return sz-ret;
}

ssize_t write(struct file *fl,const char __user *buf,size_t sz, loff_t *off){

	char *pos;
        int ret;
	dbuf_t *dbuf = fl->private_data;
	pr_info("%s: Invoked\n",__FUNCTION__);
        if(sz<0) return -EINVAL;

	mutex_lock_interruptible(&dbuf->mtx);
	if(sz > dbuf->buf_size)
                       sz = dbuf->buf_size;
        if(sz+*off > dbuf->buf_size)
                       sz = dbuf->buf_size-*off;

        pos = dbuf->buf + *off;
        ret = copy_from_user(pos,buf,sz);
        *off += sz;
	mutex_unlock(&dbuf->mtx);
	return sz-ret;
}

loff_t lseek(struct file *fl, loff_t off, int whence){

	dbuf_t *dbuf = fl->private_data;
	pr_info("%s: Invoked\n",__FUNCTION__);
	
        if(off<0)
                 return -EOVERFLOW;

	mutex_lock_interruptible(&dbuf->mtx);
        switch(whence){

                case SEEK_SET:
                                fl->f_pos = off;
                                break;
                case SEEK_CUR:
                                fl->f_pos += off;
                                break;

                case SEEK_END:
				fl->f_pos = dbuf->buf_size + off;
                                break;
                default:
                                pr_info("%s: Invalid Whence\n",__FUNCTION__);
                                return -EINVAL;
                }

	(fl->f_pos > dbuf->buf_size) ?  fl->f_pos=dbuf->buf_size : fl->f_pos;
	mutex_unlock(&dbuf->mtx);
//	pr_info("off: %llu \n",fl->f_pos);
        return fl->f_pos;

}

int release(struct inode *in,struct file *fl){

	//dbuf_t *dbuf = fl->private_data;

	pr_info("%s: Invoked\n",__FUNCTION__);
	
	return SUCCESS;

}


struct file_operations fops = FOPS_INIT;
			/*	{
				.owner = THIS_MODULE,
				.open = open,
				.read = read,
				.write = write,
				.release = release,
				.llseek = lseek
				};
			*/
struct class *cls;
int minor = 2;  //Beware of local and global declarations since they shudnt match and shudnt redefined..
dev_t devid;

int __init init_module(void){

	int i;
	pr_info("%s: Loaded\n",__FUNCTION__);
	pRiV=kzalloc(sizeof(dpri_t),GFP_KERNEL);
	if(!pRiV){
		pr_info("%s: Device private data failed\n",__func__);
		return -EFAULT;
		}
	alloc_chrdev_region(&devid,0,2,DEV_NAME);
	cdev_init(&pRiV->cdev,&fops);

	cdev_add(&pRiV->cdev,devid,2);

	cls = class_create(THIS_MODULE,"VCLASS");
	if(!cls)
		pr_info("cls: ERROR\n");

	for(i=0;i<minor;i++)
		device_create(cls,NULL,devid+i,NULL,"buf%d",i);
		
	return SUCCESS;
}

void cleanup_module(void){

	int i;
	for(i=0;i<minor;i++){
                device_destroy(cls,devid+i);
                }
	class_destroy(cls);
	cdev_del(&pRiV->cdev);
	unregister_chrdev_region(devid,minor);
	/*free buffers*/
	for(i=0;i<BUFCOUNT;i++){
		while(mutex_is_locked(&pRiV->dbuf[i].mtx));
			kfree(pRiV->dbuf[i].buf);
		}
	kfree(pRiV);
	pr_info("%s: Unloaded\n",__FUNCTION__);

}

MODULE_LICENSE("GPL");
