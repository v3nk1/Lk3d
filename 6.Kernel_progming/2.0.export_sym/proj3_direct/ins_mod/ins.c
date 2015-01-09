#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

#include"../headers.h"//it has structure defination

//struct fptrs obj;

void func1(int i){

	pr_info("i: %d\n",i);
	
}

void func2(char *str){

	pr_info("str: %s\n",str);

}

int __init init_module(void){

	pr_info("Module: ins inserted\n");
//	obj.fptr1 = func1;
//	obj.fptr2 = func2;

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module: ins removed\n");

}

//EXPORT_SYMBOL(obj); 	//if u want to pass 2 functions as a single symbol then uncomment it
EXPORT_SYMBOL(func1);
EXPORT_SYMBOL(func2);

MODULE_LICENSE("GPL");
