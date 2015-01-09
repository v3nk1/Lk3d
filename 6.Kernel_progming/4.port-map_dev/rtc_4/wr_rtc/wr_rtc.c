#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include"../MACROS.h"

extern void rd_rtc(void);

int init_module(void){

	__WR_HOUR(0x19);
	return 0;

}

void cleanup_module(void){

	rd_rtc();
	pr_info("Module removed\n");

}


MODULE_LICENSE("GPL");
