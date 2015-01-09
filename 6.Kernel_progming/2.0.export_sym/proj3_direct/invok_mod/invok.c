#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

#include"../headers.h"

//extern struct fptrs obj;
extern void func1(int);
extern void func2(char *);

int __init init_module(void){

	pr_info("Module: invok inserted\n");

//		obj.fptr1(987);//invoking func1
//		obj.fptr2("venky");//invoking func2
		func1(987);
		func2("abcdef");

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: invok removed\n");

}

MODULE_LICENSE("GPL");
