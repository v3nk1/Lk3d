#include"headers.c"
#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

int gif_canHandle(const char *name){
	int len=strlen(name)-3;
	name=name+len;
	if(!strcmp(name,"gif")) return TRUE;
	else return -1;
}

void gif_displayImage(const char *name){
int ret=gif_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else printf("oprtns u can perform on %s file:\n",name);
}

void gif_saveImage(const char *name){
int ret;
char type[4];
ret=gif_canHandle(name);
if(ret<0) printf("cannot handle %s file\n",name);
else{
	printf("enter image format u want to conv to:");
	scanf("%s",type);
	printf("image is conv from %s to %s","gif",type);
	}
}

sh gifHandler={gif_canHandle,gif_saveImage,gif_displayImage};
