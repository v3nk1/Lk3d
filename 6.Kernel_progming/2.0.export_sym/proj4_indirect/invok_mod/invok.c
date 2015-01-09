#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

#include"../headers.h"

struct fptrs *pobj;//structure pointer to store the return address of __symbol_get func..

int __init init_module(void){

	pr_info("Module: invok inserted\n");
	pobj = __symbol_get("obj");

	if(pobj){
		pobj->fptr1(987);//invoking func1
		pobj->fptr2("venky");//invoking func2
		}
	else
		pr_info("obj: No such symbol\nFirst insert ins.ko\n");

	return 0;

}

void __exit cleanup_module(void){

	if(pobj)
		__symbol_put("obj");

	pr_info("Module: invok removed\n");

}

MODULE_LICENSE("GPL");
