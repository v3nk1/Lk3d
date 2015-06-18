//Its a shared interrupt line (IRQ) registration..

#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/interrupt.h>
#include<linux/irq.h>
#include<linux/init.h>

#define SH_IRQ	1			/*Its a shared irq for eth0*/

int irq=SH_IRQ,intrr_cnt,devid;
module_param(irq,int,0644);

void softhand(struct softirq_action *sa){

	pr_info("%s: Invoked\n",__func__);

}

irqreturn_t my_intrrupt_hand(int irq,void *devid){

	intrr_cnt++;
	pr_info("ISR: called %d times\n",intrr_cnt);
	//pr_info("@%d\n",MY_SOFTIRQ_SOFTIRQ);
	raise_softirq(MY_SOFTIRQ);
	return IRQ_NONE;	

}	

int __init init_module(void){

	if(request_irq(irq,my_intrrupt_hand,IRQF_SHARED,"my_shared_intrr",&devid)){
							pr_info("req_irq: Failed\n");
							return -1;
							}
	open_softirq(MY_SOFTIRQ,softhand);
	pr_info("Registered interrupt module for irq %d\n",irq);
	return 0;

}

void __exit cleanup_module(void){

	synchronize_irq(irq);
	raise_softirq_irqoff(MY_SOFTIRQ);
	free_irq(irq,&devid);
		/*devid is used to identify when removing(must needed when shared irq line)*/
	pr_info("UnRegistered interrupt module for irq %d\n",irq);

}

MODULE_LICENSE("GPL");
