#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

int *psym;

int __init init_module(void){

	pr_info("Module: rd inserted\n");
	psym = __symbol_get("i");
	if(psym)
		pr_info("i: %d\n",*psym);
	else	
		pr_info("i: No such symbol\n");

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: rd removed\n");
	if(psym)
		__symbol_put("i");

}

MODULE_LICENSE("GPL");
