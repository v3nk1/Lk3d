#include<stdio.h>
int temp_pass,temp_resume,temp_play,temp_stop;
int temp_load;

int mediaHandler(char *name){
if(!strcmp(name+strlen(name)-3,"mp3"))  return 1;
else return -1;
}

void loadMedia(void){
char name[25];
printf("enter name of file u want to open: ");
scanf("%s",name);
int ret=mediaHandler(name);
if(ret==1) temp_load=123,printf("media is loaded\n");
else printf("unrecognized format\n");
}

void playMedia(void){
if(temp_load==123) printf("media is playing\n");
else printf("first load the media\n");
temp_pass=123;temp_stop=123;temp_play=123;

}

void stopMedia(void){
if(temp_load==123){ 
	if(temp_stop==123||temp_pass==123||temp_resume==123) temp_pass=0,temp_stop=0,temp_resume=0,printf("media is stopped\n");
	else printf("no media loaded to stop\n");}
else printf("no media loaded to stop\n");

}

void pauseMedia(void){
if(temp_load==123){
	if(temp_pass==123){ temp_resume=123,temp_pass=0,printf("media is paused\n");return;}
	if(temp_play==0) printf("no media playing\n");
	if(temp_resume==123) temp_resume=0,temp_pass=123, printf("media is resumed\n");
	}
else printf("no media loaded to do action\n");
}
