#include<stdio.h>
#include<string.h>
extern void menu(void);

void showImage(void){
char name[25];
printf("enter file name with extension: ");
scanf("%s",name);
if(!strcmp(name+strlen(name)-3,"gif")) 
	printf("optnts perform on file:\n");

else printf("cannot handle\n");
}

void convImage(void){
char name[25];
printf("enter source file name with extension: ");
scanf("%s",name);
if(!strcmp(name+strlen(name)-3,"gif")){ 

	char type[4];
	printf("enter the extension conv to: ");
	scanf("%s",type); 
}

else printf("cannot handle\n");

}
