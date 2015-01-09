#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

int __init init_module(void){

	struct thread_info *ti;
	
	ti=current_thread_info();
	
	//Here "__FUNCTION__" prints the current invoking function
	pr_info("(%s)ref: %p\n",__FUNCTION__,current_thread_info()->task);	// 1shot step
	pr_info("(%s)ref: %p\n",__FUNCTION__,ti->task);

	return 0;

}

void __exit cleanup_module(void){

	pr_info("Module removed\n");

}

MODULE_LICENSE("GPL");
