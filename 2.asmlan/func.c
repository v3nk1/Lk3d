#include<stdio.h>
sum(int x,int y){
printf("%d\n", x+y);
}
main(){
static int a,b;
a=1,b=2;
int c=sum(a,b);
//printf("%d\n",c);
}

//int a,b;
