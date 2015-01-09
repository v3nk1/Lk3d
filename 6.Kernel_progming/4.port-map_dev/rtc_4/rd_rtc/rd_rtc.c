#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

#include"../MACROS.h"

void rd_rtc(void){

	int date,mon,year;
	int hr,min,sec;

	__RD_SEC(sec);//semi-colon is not necessary
	__RD_MIN(min);
	__RD_HOUR(hr);

	__RD_DATE(date);
	__RD_MON(mon);
	__RD_YEAR(year);

	pr_info("time: %02x:%02x:%02x\n",hr,min,sec);
	year += 0x2000;

	min += 0x30;
	if(min >= 60){
		min -= 0x60;
//		hr += 0x1;
		}
	
//	hr += 0x5;
/*	if(hr > 0x9){
		hr = hr + 0x6;
		}
*/	
	pr_info("time: %02x:%02x:%02x\n",hr,min,sec);
	pr_info("date: %02x/%02x/%x\n",date,mon,year);


}

int init_module(void){

	pr_info("Module: Cal inserted\n");
	return 0;

}

void cleanup_module(void){
	
	rd_rtc();
	pr_info("Module removed\n");

}

EXPORT_SYMBOL_GPL(rd_rtc);

MODULE_LICENSE("GPL");
