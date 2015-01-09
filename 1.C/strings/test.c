#include<stdio.h>
#include<string.h>
main(){

int a[10]={1,2,3,4,5},b[10];
memcpy(b,a,8);

printf("%d %d %d %d %d %d",b[0],b[1],b[2],b[3],b[4],b[5]);
}

