#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/moduleparam.h>

int k=100;		 // you can pass this val by cmd-line arg while doing "insmod modparam.ko k=500"
module_param(k,int,0644);//Dont give 0666
			/* Permissions to access for that particular file named as k. 
				Permissions: Ur well known octal numbers as in open API;
				U = 4-2-1: rd:wr:exe ==> U = 4(rdonly) / 4+2(rd+wr)
				G = 4-2-1: rd:wr:exe		,,         ,,
				O = 4-2-1: rd:wr:exe
			  ===> 3rd arg is 0UGO //Here UGO are values	
		     >>====--> IMP: if 0666 given, will cause error
			
			Module_param stores the k value in file in  /sys/modules/<ur-loaded-module-name>/parameters

			Here the parameters is a directory created if and only if u invoke module_param
				ls -l /sys/module/modparam/parameters/
				cat /sys/module/modparam/parameters/k
				echo 2000 > /sys/module/modparam/parameters/k

*/

int __init init_module(void){

	pr_info("Module inserted\n");
	pr_info("%s : k= %d\n",__FUNCTION__,k);
	return 0;
}

void __exit cleanup_module(void){

	pr_info("%s : k= %d\n",__FUNCTION__,k);
	pr_info("Module removed\n");

}

MODULE_LICENSE("GPL");
