#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

void SaMpLe_FuNc(void){

	pr_info("\n*********************************************************\n");
	pr_info("|            Hello!! Welcome to Linux-13.10             |\n");
	pr_info("*********************************************************\n\n");

}
EXPORT_SYMBOL(SaMpLe_FuNc);//To check in cat /proc/kallsyms | grep SaMpLe_FuNc

int init_module(void){

	printk("module inserted\n");
	SaMpLe_FuNc();
	return 0; /* returning -ve values are not permitted*/
	
}

void cleanup_module(void){

	printk("module removed\n");

}

MODULE_DESCRIPTION ("qwertyuio");
MODULE_AUTHOR ("ASDF");
MODULE_LICENSE ("GPL");


/*
 * "insmod" is a user space program(executable) used to load the module(.ko) into kernel.
 * To trace that execute below command
 * "strace insmod hello.ko"
 * "strace rmmod hello"
 * See what API's are internally calling..
 	-- insmod calls finit_module
	-- rmmod  calls delete_module
 */

/*
 * with both init, cleanup : normal insert and noramal remove.
 * with init, w/o cleanup : normal insert and not able to remove
 * w/o init, with cleanup : normal insert and normal remove
 * w/o both init, cleanup : normal insert and normal remove
 */
