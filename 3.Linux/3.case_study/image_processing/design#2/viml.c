#include"headers.c"
#include<stdio.h>
#define TRUE 1
#define FALSE 0

/*typedef struct handle{
		int (*canHanldle) (const char *);
		void (*saveImage) (const char *);
		void (*drawImage) (const char *);
		}sh;
*/
/*int vcanHandle(const char *name){
if(!strcmp(name+strlen(name)-3,"gif")) return TRUE;//printf(".gif: we can handle\n");
else return FALSE;
}*/

//sh jpg={jpg_canHandle,jpg_saveImage,jpg_drawImage}; give it inthe appropriate modules.
//sh tif={tif_canHandle,tif_saveImage,tif_displayImage};

sh *handlers[]={&gifHandler,&jpgHandler,&tifHandler,NULL};

//handle *imagehandlers[]={gif_handler,jpg_handler,tif_handler};

int findHandler(const char *name){
	int index=0,ret;
	for(;handlers[index]!=NULL;index++){
		ret=handlers[index]->canHandle(name);
		if(ret==1) return index;//very very importent to locate
	}
return -1;
			
}

void vdisplayImage(const char *name){
	int ret;
	ret=findHandler(name);
	if(ret<0) {printf("cannot handle %s file\n",name);return;}
	else    printf("we can handle\n"),
		handlers[ret]->displayImage(name);   //call back functions
		
}

void vsaveImage(const char *name){
	int ret;
	ret=findHandler(name);
	if(ret<0){ printf("cannot handle %s file\n",name);return;}
	else handlers[ret]->saveImage(name);   //call back functions
}
