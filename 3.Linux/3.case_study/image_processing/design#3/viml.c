#include"headers.c"
#include<dlfcn.h>
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
void *lib;

void vloadHandlers(void){
FILE *fp;
fp=fopen("./config.txt","r");
if(!fp) perror("fopen"),exit(2);
char lib_buff[25];//="./lib_gif.so";
while(1){
	void *p=fgets(lib_buff,sizeof(lib_buff),fp);
//printf("len=%lu \n",strlen(lib_buff));
	lib_buff[strlen(lib_buff)-1]='\0';
	//lib_buff[12]='\0';
	//getchar();
	if(!p) break;int i;//printf("%u %u\n",lib_buff,p);
	//for(i=0;i<25;i++);
	//printf("%d i=%d ,%c\n",'\n',lib_buff[i],lib_buff[i]);
	lib=dlopen(lib_buff,RTLD_NOW); 
	if(!lib) printf("%s\n",dlerror()),exit(4);
	}	
//dlclose(lib);  library is unloaded here, so error
fclose(fp);	
}

int findHandler(const char *name){
	//printf("vfindHadler START is success\n");
	
	int index=0;int ret=0;
	//printf("success\n");
	//int ret=0;
	//printf("index=%d",index_val);// its not working
	for(index=0 ; index<no_libs ;index++ ){
		//printf("vfindHandler FOR LOOP IS EXECUTED\n");
		ret=(handlers[index]->canHandle)(name);
		if(ret==1){ /*printf("$$$$$$$$$ %d\n",index); */return index;}//very very importent to locate
	}
//printf("vfindHandler END is success\n");
return -1;
			
}

void vdisplayImage(const char *name){
//	printf("vdisplayImage START is success");
	
	int ret;
	ret=findHandler(name);
	if(ret<0) {printf("cannot handle %s file\n",name);return;}
	else    printf("we can handle\n"),
		handlers[ret]->displayImage(name);   //call back functions
		
//	printf("vdisplayImage END is success");
}

void vsaveImage(const char *name){
//	printf("vsaveIMAGE start is executed\n");
	int ret;
	ret=findHandler(name);
	if(ret<0){ printf("cannot handle %s file\n",name);return;}
	else handlers[ret]->saveImage(name);   //call back functions
//printf("vsaveImage END\n");
}
