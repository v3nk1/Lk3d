#include"headers.c"
#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

int jpg_canHandle(const char *name){
	int len=strlen(name)-3;
	name=name+len;
	if(!strcmp(name,"jpg")) return TRUE;
	else return -1;
}

void jpg_displayImage(const char *name){
int ret=jpg_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else printf("oprtns u can perform on %s file:\n",name);
}

void jpg_saveImage(const char *name){
int ret;
char type[4];
ret=jpg_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else{
	printf("enter image format u want to conv to:");
	scanf("%s",type);
	printf("\nimage is conv from %s to %s","jpg",type);
	}
}

sh jpgHandler={jpg_canHandle,jpg_saveImage,jpg_displayImage};
