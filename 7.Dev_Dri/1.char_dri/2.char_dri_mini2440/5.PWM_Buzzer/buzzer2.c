#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/io.h>

void *conf,*data,*pullup;
int __init init_module(void){

	pr_info("%s: Invoked\n",__func__);
	conf=ioremap(0x56000010,12);
	data=conf+4;
	pullup=data+4;

	iowrite32(0x01,conf);
	iowrite32(ioread32(pullup)^1,pullup);
	iowrite32(ioread32(data)^1,data);

	return 0;
}

void __exit cleanup_module(void){
	
	pr_info("1.%s: Invoked\n",__func__);

	iowrite32(ioread32(data)^1,data);
	iowrite32(0x0,pullup);
	iowrite32(0x0,conf);

}

MODULE_LICENSE("GPL");
