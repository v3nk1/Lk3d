#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>

extern int i;

int __init init_module(void){

	pr_info("Module: wr_mod has inserted\n");
	i=100;

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: rd_mod has removed\n");

}


MODULE_LICENSE("GPL");
