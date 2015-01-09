#include<stdio.h>
#define STAT(a,pos)   if(a&1<<pos) printf("true\n");
main(){
unsigned int a=10,pos=1;
STAT(a,pos)
#undef STAT  // here macro name is must..
STAT(a,pos)  //after #undef macro STAT is no more..
}
