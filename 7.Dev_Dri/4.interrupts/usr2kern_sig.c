/*
 * Write a program to send a signal to user-space from
 * kernel space to current process when a key has been hitted.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/signal.h>
#include <linux/sched.h>

#define IRQ 1
int devid,flag;
dev_t dev;

irqreturn_t isr_hand(int irq,void *devp){
	
	if(flag)
		send_sig(SIGRTMAX,current_thread_info()->task,SEND_SIG_NOINFO);
	
	return IRQ_HANDLED;
}

int drv_open(struct inode *in, struct file *fp){
	
	pr_info("%s: Invoked\n",__func__);
	flag=1;
	return 0;
}

int drv_close(struct inode *in, struct file *fp){ 

	pr_info("%s: Invoked\n",__func__);
	flag=0;
        return 0;
}

struct file_operations fops = {
		.owner=THIS_MODULE,
		.open=drv_open,
		.release=drv_close,
		};

struct cdev *cdev;
struct class *cls;
struct device *device;

int register_char_driver(void){

        int ret;
        
	ret=alloc_chrdev_region(&dev,0,1,"usr2kern_char");
        if(ret<0){
                pr_info("%s: Failed to aquire major no\n",__func__);
                goto fail;
                }

        cdev=cdev_alloc();
        if(unlikely(!cdev)){
                pr_info("%s: Failed to aquire cdev object\n",__func__);
                goto unreg_chr;
                }

        cdev_init(cdev,&fops);

        if(cdev_add(cdev,dev,1)){
                pr_info("%s: Failed to add to cdev list\n",__func__);
                goto del_cdev;
                }

        cls=class_create(THIS_MODULE,"usr2kern-sig");
        if(!cls){
                pr_info("%s: Failed to create class\n",__func__);
                goto del_cdev;
                }

        device=device_create(cls,NULL,dev,NULL,"u2k");
        if(!device){
                pr_info("%s: Failed to create class\n",__func__);
                goto dest_cls;
        }

        return 0;

dest_cls:
        class_destroy(cls);
del_cdev:
        cdev_del(cdev);
unreg_chr:
        unregister_chrdev_region(dev,1);
fail:
        return -1;

}

void unregister_char_driver(void){

	device_destroy(cls,dev);
        class_destroy(cls);
        cdev_del(cdev);
        unregister_chrdev_region(dev,1);
}

int __init init_module(void){

	pr_info("%s: Invoked\n",__func__);
	if(request_irq(IRQ,isr_hand,IRQF_SHARED,"usr2kern-sig",&devid)<0){
		pr_err("%s: requset_irq failed\n",__func__);
		return -1;
		}
	register_char_driver();

	return 0;
}

void __exit cleanup_module(void){

	synchronize_irq(IRQ);
	free_irq(IRQ,&devid);
	unregister_char_driver();
	pr_info("%s: Invoked\n",__func__);

}

MODULE_LICENSE("GPL");
