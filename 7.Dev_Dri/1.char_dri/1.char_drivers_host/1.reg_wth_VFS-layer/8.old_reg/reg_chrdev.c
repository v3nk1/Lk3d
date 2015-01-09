#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

int dri_open(struct inode *in,struct file *fl){
	
	int minor;
	minor = MINOR(in->i_rdev);
	//or use minor = iminor(in);

	pr_info("%s : Invoked\n",__FUNCTION__);
	pr_info("Minor : %d\n",minor);
	return 0;
	
}

struct file_operations fops = {
				.owner =  THIS_MODULE,
				.open  =  dri_open
				};

int major;//unique for driver code
struct class *cls;
int minor_cnt=2; //no,, devices associated with this diver code

int __init init_module(void){

	int i;
	pr_info("%s : Loaded\n",__FUNCTION__);
	major = register_chrdev(0,"oldDev123",&fops);
		/*
		 * it defaultly support 256 minor no..
		 * if u want register with another kernel function such as misc or register_chrdev_region
		 *	u must specify the count of minor num u want to use, but here no need, it support 256 minors.
		 *	see the implementation of __register_chrdev
		 * Anyway in userspace u hav to create 2 device nodes seperately
		 */
		
	
	if(major<0){
		pr_info("Major: Aquiring failed\n");
		return -1;
		}
	pr_info("Major: %d aquired\n",major);
	
	cls = class_create(THIS_MODULE,"VIRTUAL");
	for(i=0;i<minor_cnt;i++){//creating 2 device nodes in userspace
		dev_t devt = MKDEV(major,i);
		device_create(cls,NULL,devt,NULL,"oldDev%d",i);
		}

	return 0;
}

void __exit cleanup_module(void){

	int i;
	pr_info("%s : Unload\n",__FUNCTION__);

        for(i=0;i<minor_cnt;i++){//destroying 2 device nodes in userspace
                dev_t devt = MKDEV(major,i);
		device_destroy(cls,devt);
                }
	class_destroy(cls);
	unregister_chrdev(major,"oldDev123");
	
}

MODULE_LICENSE("GPL");
