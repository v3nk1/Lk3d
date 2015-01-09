#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

main(){

	int (*add)(int,int);
	int (*sub)(int,int);
	void *dl=dlopen("./libxyz.so",RTLD_LAZY/*RTLD_NOW*/);
	if(dl==NULL){
		printf("1. %s\n",dlerror());
		exit(1);
		}
	sub=dlsym(dl,"sub");
	if(sub==NULL){
		printf("2. %s\n",dlerror());
		exit(2);
		}
	printf("Sub: %d\n",sub(10,20));

}
