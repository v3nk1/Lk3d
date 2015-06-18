#include <linux/module.h>
#include <linux/version.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include "list.h"

list_t list1;

int init_module(void){
	pr_info("%s: Invoked\n",__func__);
	init_list(&list1);
	insert(&list1,10);
	insert(&list1,20);
	insert(&list1,30);

	return 0;
}

void cleanup_module(void){

	pr_info("%s: Invoked\n",__func__);
	print(&list1);
	insert(&list1,40);
	print(&list1);
		/*Compulsory pass &list1 otherwise system hang*/

}

MODULE_LICENSE("GPL");
