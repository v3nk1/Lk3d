/*
 * Demonstrating the use of mutex_lock/_killable/_interruptible().
 * Contending application:
   -----------------------
	Means that lets say 2 applications are running in user-space.
	App1: 	Is holding a mutex and is doing Critical work in the driver.
		Observer that no lock is held in application.
		In the driver read we kernel is doing some critical job behalf of 
		the application while holding a mutex lock. Its not terminated yet.
	App2:	Meanwhile application 2 trying to aquire the mutex_lock. Because
		of App1 is holding the lock, application 2 will going to block/sleep until
		app1 release the lock. Its called contension(contending).
		Run in the 2nd tab.
	
	So the app starving/begging for lock is called contending application.

 * Check:
	open 3rd tab
	Generate a signal to second ran app, see ps -Af and generate signal
	using 'kill'
 */	

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define FOPS 	{			\
		.owner=THIS_MODULE,	\
		.read=read,		\
		.open=open,		\
		.release=close,		\
		}

DEFINE_MUTEX(mtx);

struct cdev *cdev;
struct class *cls;
struct device *device;
dev_t dev;

static inline void mysleep(unsigned sec)
{
        current->state = //TASK_UNINTERRUPTIBLE;
				/*
				 * Since we are demonstrating signals we cannot prevent
				   the process from receiving all signals.
				 * So don't do this.
				 */
			   TASK_INTERRUPTIBLE;
				/*
				 * This can be awaken by any signal now, but that
				   depends that you are using only 'killable' or 'interruptible'
				 */
        schedule_timeout(sec * HZ);
}

int open (struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__func__);
	return 0;

}

ssize_t read(struct file *fl, char __user *buf, size_t sz, loff_t *off){

	pr_info("%s: Invoked\n",__func__);
	
	pr_info("%s:%s-%u: Trying to acquire the lock..\n",__func__,current_thread_info()->task->comm,
		current_thread_info()->task->pid);


/*All are deadlock scenarios*/

	//mutex_lock(&mtx);
		/*
		 * Nothing cannot interrupt the contending application. Means 2nd application.
		 */
	if(mutex_lock_interruptible(&mtx)==-EINTR)			\
		pr_info("%s: Got a signal, interrupted\n",__func__);
		/*
		 * Any signal can interrupt/terminate the contending application.
		 */
	//mutex_lock_killable(&mtx);
		/*
		 * Only SIGKILL(9) signal can interrupt/terminate the contending application.
		 * But here also any signal is able to interrupt the process.
		 */

	pr_info("%s:%s-%u: Acquired the lock\n",__func__,current_thread_info()->task->comm,
		current_thread_info()->task->pid);

	mysleep(3*60);
		/*
		 * Blocking here using sleep;
		 * Within this time only we have to send signals.
		 */

	mutex_unlock(&mtx);
	pr_info("%s:%s-%u: Released the lock\n",__func__,current_thread_info()->task->comm,
		current_thread_info()->task->pid);

	return 10;

}

int close (struct inode *in, struct file *fl){

	pr_info("%s: Invoked\n",__func__);
	return 0;

}
struct file_operations fops=FOPS;

int __init init_module(void){

	int ret;
	pr_info("%s: Invoked\n",__func__);

	ret=alloc_chrdev_region(&dev,0,1,"mtx-test");
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
	
	cls=class_create(THIS_MODULE,"mutex-test");
	if(!cls){
		pr_info("%s: Failed to create class\n",__func__);
		goto del_cdev;
		}

	device=device_create(cls,NULL,dev,NULL,"testdev");
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

void __exit cleanup_module(void){

	pr_info("%s: Invoked\n",__func__);
	device_destroy(cls,dev);
	class_destroy(cls);
	cdev_del(cdev);
	unregister_chrdev_region(dev,1);

}

MODULE_LICENSE("GPL");
