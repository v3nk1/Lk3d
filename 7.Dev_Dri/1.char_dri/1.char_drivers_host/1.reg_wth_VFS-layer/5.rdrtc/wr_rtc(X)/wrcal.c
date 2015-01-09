#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
//#include"MACROS"

extern void calender(void);

int init_module(void){

	calender();
	return 0;

}

void cleanup_module(void){

	pr_info("Module removed\n");

}


MODULE_LICENSE("GPL");
