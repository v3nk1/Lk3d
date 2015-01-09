#include <stdio.h>
#include <dlfcn.h>

main(){

	if(!dlopen("./lib_jpg.so",RTLD_NOW))
		printf("%s\n",dlerror());

}
