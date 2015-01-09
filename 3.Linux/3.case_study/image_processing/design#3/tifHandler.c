#include"headers.c"
#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

int tif_canHandle(const char *name){
	int len=strlen(name)-3;
	name=name+len;
	if(!strcmp(name,"tif")) return TRUE;
	else return -1;
}

void tif_displayImage(const char *name){
int ret=tif_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else printf("oprtns u can perform on %s file:\n",name);
}

void tif_saveImage(const char *name){
int ret;
char type[4];
ret=tif_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else{
	printf("enter image format u want to conv to:\n");
	scanf("%s",type);
	printf("image is conv from %s to %s","tif",type);
	}
}

sh tifHandler={tif_canHandle,tif_saveImage,tif_displayImage};

int _init(){
reg_handler(&tifHandler);
printf("registerd tif support\n");
}

int _fini(){
printf("unregistered tif support\n");
}

