#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

extern int icounter;

int __init init_module(void){

	pr_info("Module: read inserted\n");
	pr_info("val i: %i\n",icounter);

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: read removed\n");

}

MODULE_LICENSE("GPL");
