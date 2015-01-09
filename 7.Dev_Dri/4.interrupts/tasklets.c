#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>

int irq=1;
void taskfunc(unsigned long data){

	static int count;
	pr_info("%s: Invoked-%d:%lu\n",__func__,++count,data);	

}

DECLARE_TASKLET(mytasklet,taskfunc,1234);

irqreturn_t intrpthand(int i,void *devid){

	static int icount;
	pr_info("%s: Invoked-%d\n",__func__,++icount);
	pr_info("#%d\n",i);
	tasklet_schedule(&mytasklet);	

	return IRQ_HANDLED;

}

int dev;
static int __init task_init(void){

	pr_info("%s: Invoked\n",__func__);
	request_irq(irq,intrpthand,IRQF_SHARED,"myinterrupt",&dev);

	return 0;
}

static void __exit task_exit(void){

	tasklet_kill(&mytasklet);
	free_irq(irq,&dev);
	pr_info("%s: Invoked\n",__func__);

}

module_init(task_init);
module_exit(task_exit);

MODULE_LICENSE("GPL");
