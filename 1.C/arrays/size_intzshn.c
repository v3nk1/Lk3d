#include<stdio.h>
main(){
int s=5;
int a[s];   //we are unable to initialize at the time of declaration means like a[s]={1,3}. since what happened if size is changed.
a[0]=1;a[1]=2;a[2]=3;
printf("%d %d %d\n",a[0],a[1],a[2]);
}
