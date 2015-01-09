#include<stdio.h>
#include"headers.h"
extern findHandler(char *name);
int temp_pass,temp_resume,temp_play,temp_stop;
int temp_load;
char *temp_name;

int mp4_mediaHandler(char *name){
if(!strcmp(name+strlen(name)-3,"mp4"))  return 1;
else return -1;
}

void mp4_loadMedia(char *name){temp_name=name;
//char name[25];
//printf("enter name of file u want to open: ");
//scanf("%s",name);
int ret=mp4_mediaHandler(name);
if(ret==1) temp_load=123,printf("media is loaded\n");
else printf("unrecognized format\n");
}

void mp4_playMedia(void){
if(temp_load==123) printf("media is playing\n");
else printf("first load the media\n");
temp_pass=123;temp_stop=123;temp_play=123;

}

void mp4_stopMedia(void){
if(temp_load==123){ 
	if(temp_stop==123||temp_pass==123||temp_resume==123) temp_pass=0,temp_stop=0,temp_resume=0,printf("media is stopped\n");
	else printf("no media loaded to stop\n");}
else printf("no media loaded to stop\n");

}

void mp4_pauseMedia(void){
if(temp_load==123){
	if(temp_pass==123){ temp_resume=123,temp_pass=0,printf("media is paused\n");return;}
	if(temp_play==0) printf("no media playing\n");
	if(temp_resume==123) temp_resume=0,temp_pass=123, printf("media is resumed\n");
	}
else printf("no media loaded to do action\n");
}

void mp4_convMedia(void){
if(temp_load==123){
        char type[4];
        printf("enter the format u want to conv to:");
        scanf("%s",type);
	int ret_conv=findHandler(type);
        if(ret_conv!=-1) printf("%s convrted to %s\n",".mp4",type);
        else printf("un recognized format\n");
        }
else printf("first load the media\n");
}


sh mp4={&mp4_mediaHandler,&mp4_loadMedia,&mp4_playMedia,&mp4_stopMedia,&mp4_pauseMedia,&mp4_convMedia};
                            
