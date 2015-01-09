#include<stdio.h>

void *my_memcpy(void *a,const void *b,int sz){
int i=0;
for(; i<sz;i++){
*((char*)a+i)=*((char*)b+i);
}
//return a;
}


main(){
char a[6];
char b[6]="iknev";
my_memcpy(a,b,(sizeof (char))*4);
printf("%c %c %c %c %c %c",a[0],a[1],a[2],a[3],a[4],a[5]);
}
