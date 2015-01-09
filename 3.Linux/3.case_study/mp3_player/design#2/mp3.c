#include<stdio.h>
#include"headers.h"
extern int findHandler(char *name);
int temp_pass,temp_resume,temp_play,temp_stop;
int temp_load;
extern char temp_name[25];


int mp3_mediaHandler(char *name){
if(!strcmp(name+strlen(name)-3,"mp3"))  return 1;
else return -1;
}

void mp3_loadMedia(char *name){
//char name[25];
//printf("enter name of file u want to open: ");
//scanf("%s",name);
int ret=mp3_mediaHandler(name);
if(ret==1) temp_load=123,printf("media is loaded\n");
else printf("unrecognized format\n");
}

void mp3_playMedia(void){
if(temp_load==123) printf("media is playing\n");
else printf("first load the media\n");
temp_pass=123;temp_stop=123;temp_play=123;

}

void mp3_stopMedia(void){
if(temp_load==123){ 
	if(temp_stop==123||temp_pass==123||temp_resume==123) temp_pass=0,temp_stop=0,temp_resume=0,printf("media is stopped\n");
	else printf("no media loaded to stop\n");}
else printf("no media loaded to stop\n");

}

void mp3_pauseMedia(void){
if(temp_load==123){
	if(temp_pass==123){ temp_resume=123,temp_pass=0,printf("media is paused\n");return;}
	if(temp_play==0) printf("no media playing\n");
	if(temp_resume==123) temp_resume=0,temp_pass=123, printf("media is resumed\n");
	}
else printf("no media loaded to do action\n");
}

void mp3_convMedia(void){
if(temp_load==123){ 
	char type[4];
	printf("enter the format u want to conv to:");
	scanf("%s",type);
	int ret_conv=findHandler(type);
	if(ret_conv!=-1) printf("%s convrted to %s\n",".mp3",type);
	else printf("un recognized format\n");
	}
else printf("first load the media\n");
}


sh mp3={&mp3_mediaHandler,&mp3_loadMedia,&mp3_playMedia,&mp3_stopMedia,&mp3_pauseMedia,&mp3_convMedia};
// see in above statement address operator(&) is optional.. if u remove & then also it passess address.
