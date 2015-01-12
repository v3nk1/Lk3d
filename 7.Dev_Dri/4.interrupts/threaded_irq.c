//Its a shared interrupt line (IRQ) registration..

#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/interrupt.h>
#include<linux/irq.h>
#include<linux/init.h>

#define SH_IRQ	1			/*Its a shared irq for keyboard*/
	/**
	 * 1 for laptop keyboard and PS2 keyboard
	   23 for usb keyboard. 23 is known from "cat /proc/interrupts"
		to which usb port you are connecting keyboard
	 */

int irq=SH_IRQ,intrr_cnt,devid;
module_param(irq,int,0644);
char kb_arr[]="  1234567890-=  qwertyuiop[]  asdfghjkl;'   zxcvbnm,./";
static unsigned char scancode;

irqreturn_t my_intrrupt_hand(int irq,void *devid){

	intrr_cnt++;
	pr_info("ISR: called %d times\n",intrr_cnt);
	scancode = inb(0x60);	
	
	return IRQ_WAKE_THREAD;
}	

irqreturn_t my_thrd_hand(int irq,void *devid){

	if(scancode &= 0x7f)
		pr_info("Scan Code: %d -->%c\n",scancode,kb_arr[scancode]);
	return IRQ_HANDLED;
}	

int __init init_module(void){

	if(request_threaded_irq(irq,my_intrrupt_hand,my_thrd_hand,
				IRQF_SHARED,"my_shared_intrr",&devid)){
						pr_err("req_irq: Failed\n");
						return -1;
						}
	pr_info("Registered interrupt module for irq %d\n",irq);
	return 0;

}

void __exit cleanup_module(void){

	synchronize_irq(irq);
	free_irq(irq,&devid);
		/*devid is used to identify when removing(must needed when shared irq line)*/
	pr_info("UnRegistered interrupt module for irq %d\n",irq);

}

MODULE_LICENSE("GPL");
