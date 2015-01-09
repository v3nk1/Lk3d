#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

int *ptr;

int __init init_module(void){

	pr_info("Module: wr inserted\n");
	ptr = __symbol_get("i");//ptr will be null if u first insert this module before the module where "i" has declared(ins_mod)

//## This conditional construct is must and shud, other wise(means if ptr=NULL then *NULL will causes a problem) the module will be in locked state, u cannot remove it, to remove it u shud restart..
	//In user space *NULL causess segmentation fault but here u can see some msgs in "dmesg"

	if(ptr){//found the requested symbol(ptr is not NULL) then
		*ptr = 123;
		pr_info("value updated successfully\n");
		}

	else {//if not found(ptr=NULL) then
		pr_alert("symbol doesnt found\n");
		}

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: wr removed\n");

	if(ptr)//if u didnt check this condition this also causes segmentation fault when removing and u cannt remove actually, again needs to restart..
		__symbol_put("i");
	
}

MODULE_LICENSE("GPL");
