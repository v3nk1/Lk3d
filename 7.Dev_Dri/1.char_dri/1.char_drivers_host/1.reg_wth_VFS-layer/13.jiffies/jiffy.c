/*
 If u didnt use del_timer(); Dont remove this module directly until it comletes its 5 iterations of mod_timer,
 if u remove in b/w kernel will crash.
	OR
 Just use del_timer() in cleanup_module as converse of add_timer();
 */

#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/timer.h>

struct timer_list timer;
int cnt;

void timer_func(unsigned long ul){

	cnt++;
	pr_info("%s : Invoked = %d\n",__FUNCTION__,cnt);

if(cnt<5)
	mod_timer(&timer,jiffies+HZ*10);/*1HZ=1sec*/

}

int __init init_module(void){

	pr_info("%s: Invoked\n",__FUNCTION__);
	pr_info("HZ value: %i\n",HZ);
	
	init_timer(&timer);
	timer.expires = jiffies+HZ; /*The mod_timer will update timer.expires member only*/
	timer.data = 1234;/*To pass value to timer_function(passing val to ul argument) */
	timer.function = timer_func;
	add_timer(&timer);
	pr_info("%s: exited\n",__FUNCTION__);

	return 0;	

}

void __exit cleanup_module(void){

	pr_info("%s : Invoked\n",__FUNCTION__);
	del_timer(&timer);

}

MODULE_LICENSE("GPL");
