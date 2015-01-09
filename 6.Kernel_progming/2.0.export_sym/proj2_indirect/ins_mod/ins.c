#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

static int i;

static int __init exp_init_module(void){

	pr_info("Module: ins inserted\n");
	return 0;
	
}

static void __exit exp_cleanup_module(void){

	pr_info("Module: ins removed\n");

}

module_init(exp_init_module);
module_exit(exp_cleanup_module);

EXPORT_SYMBOL(i); //if u dont export the symbol then in rd/wr module __symbol_get failed to find that symbol

MODULE_LICENSE("GPL");
