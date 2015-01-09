//Here we are inserting a global variable modules then we are exporting it such that other modules can use it

#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>

static int icounter;
	/*
	 * In module programming by default a variable or a symbol declared as global 
	 * treated as static symbol, We need to export those.
	 */

int __init init_module(void){

	pr_info("Module: Global int has inserted\n");

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: Global int has removed\n");

}

EXPORT_SYMBOL(icounter);
MODULE_LICENSE("GPL");
