#include<stdio.h>
#include"headers.c"
int no_libs;
sh *handlers[10];

void reg_handler(sh *handler){//printf("gif\n");
	handlers[no_libs]=handler;//printf("no_libs before=%d\n",no_libs);
	no_libs++;//printf("no_libs after=%d\n",no_libs);
}
