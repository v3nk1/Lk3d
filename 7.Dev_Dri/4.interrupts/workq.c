#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>

int irq=1;
int dev;
void func(struct work_struct *ws){

	static int iwork;
	pr_info("%s: Invoked-%d\n",__func__,++iwork);

}

DECLARE_WORK(mywork,func);

irqreturn_t inthand(int no,void *devid){

	pr_info("%s: Invoked\n",__func__);
	schedule_work(&mywork);
		/*
		 * The work is given to standard workqueues of kernel.
		 */
	return IRQ_HANDLED;

}

int init_module(void){

	pr_info("%s: Invoked\n",__func__);
	request_irq(irq,inthand,IRQF_SHARED,"myirq",&dev);
	return 0;

}

void cleanup_module(void){

	pr_info("%s: Invoked\n",__func__);
	/*Flush our given work form the standard workq of kernel*/
	flush_work(&mywork);
	/*
	 * To flush entire work of given workqueue queue
	 * flush_workqueue();
	 */
	/*
	 * To flush all scheduled work irrespective of specific queue
	 * flush_scheduled_work();
	 */
	free_irq(irq,&dev);

}

MODULE_LICENSE("GPL");
