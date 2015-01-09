#include<stdio.h>
main(){
char ch='A';
char *p=&ch;
printf("%d %d\n",sizeof p,sizeof (*p));
}

