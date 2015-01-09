#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>

int k[10];
module_param_array(k,int,NULL,0644);// Dont give 0666, Other mustbe 4. ie., you can give 0664/0644 but not 0666.
			/* Permissions to access for that particular file named as k. 
				Permissions: Ur well known octal numbers as in open API;
				U = 4-2-1: rd:wr:exe ==> U = 4(rdonly) / 4+2(rd+wr)
				G = 4-2-1: rd:wr:exe		,,         ,,
				O = 4-2-1: rd:wr:exe
			  ===> 3rd arg is 0UGO //Here UGO are values	
			
			Module_param stores the k value in file in  /sys/modules/<ur-module-name>/parameters

			Here the parameters is a directory created if and only if u invoke module_param
				ls -l /sys/module/modparam/parameters/
				cat /sys/module/modparam/parameters/k
				echo 10,20,30,40,50,60,70,80,90,20 > /sys/module/modparam/parameters/k
					//if u give less than 10 then ur given no.. are updated and rest will as it is.
*/

int __init init_module(void){

	int i;
	for(i=0;i<10;i++){
		k[i]=i+1;
		}
	for(i=0;i<10;i++){
	pr_info("%s : k[%d]= %d\n",__FUNCTION__,i,k[i]);
	}
	return 0;
}

void __exit cleanup_module(void){

	int i;
	for(i=0;i<10;i++){
	pr_info("%s : k[i]= %d\n",__FUNCTION__,k[i]);
	}
	pr_info("Module removed\n");

}

MODULE_LICENSE("GPL");
