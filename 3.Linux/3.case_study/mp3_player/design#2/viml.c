#include<stdio.h>
#include"headers.h"
int j;char *temp_name;
sh *handlers[]={&mp3,&mp4,NULL};

int findHandler(char *name){int i;
	int ret;
	for(i=0;handlers[i];i++){
	ret=handlers[i]->mediaHandler(name);
	if(ret==1) return i;
	}
return -1;
}

void vloadMedia(void){
char name[25];
printf("enter name of file: ");
scanf("%s",name);temp_name=name;
int ret=findHandler(name);j=ret;
if(ret==-1) printf("cannt handle this format\n");
else
handlers[j]->loadMedia(name);
}
void vplayMedia(void){

handlers[j]->playMedia();
}
void vstopMedia(void){
handlers[j]->stopMedia();

}
void vpauseMedia(void){
handlers[j]->pauseMedia();

}
void vconvert(void){
handlers[j]->convMedia();

}
