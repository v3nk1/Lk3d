#include<stdio.h>
#include<dlfcn.h>
#include<string.h>


main(){

	void *lib;
	int (*fp)(int ,int);
	lib=dlopen("./lib_add.so",RTLD_NOW);
	if(!lib) 
		perror("dlopen"),exit(1);
	fp=dlsym(lib,"add");

	printf("%d\n",(*fp)(12,34));

}
