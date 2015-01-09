#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>

int irq=1;
int dev;
struct workqueue_struct *myworkq;

void func(struct work_struct *ws){

	static int iwork;
	pr_info("%s: Invoked-%d\n",__func__,++iwork);

}

DECLARE_WORK(mywork,func);

irqreturn_t inthand(int no,void *devid){

	pr_info("%s: Invoked\n",__func__);
	queue_work(myworkq,&mywork);
	return IRQ_HANDLED;

}

int init_module(void){

	pr_info("%s: Invoked\n",__func__);
	myworkq=create_workqueue("myworkq");
	request_irq(irq,inthand,IRQF_SHARED,"myirq",&dev);
	return 0;

}

void cleanup_module(void){

	pr_info("%s: Invoked\n",__func__);
	destroy_workqueue(myworkq);
	free_irq(irq,&dev);

}

MODULE_LICENSE("GPL");
