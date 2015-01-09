#include<stdio.h>

main(){
FILE *fp1,*fp2,*fp3;
fp1=fopen("./fileno.c","r");
printf("fp1=fd= %d\n",fp1->_fileno);
fp2=fopen("./fileno.c","r");
printf("fp1=fd= %d\n",fp2->_fileno);
fp3=fopen("./fileno.c","r");
printf("fp1=fd= %d\n",fp3->_fileno);

}










/**************************************************************************************************************
NOTES:
``````	See here  in stdio.h library file there is one structure memeber that is  _fileno . so we can access it by just including library itself.
	FILE is a predefined structure pointer.
	so fopen just returning the address of the file-discriptor value(&fd);

****************************************************************************************************************/
