#include<stdio.h>
#define SET_POS(no,pos) no|1<<pos
#define PRNT_BITS(c,SIZE) int i=SIZE *8 -1;for(;i>=0;i--) printf("%d ",c>>i&1);printf("\n");
#define SIZE sizeof(no)
main(){
unsigned int no=10,pos=4,c;
c=SET_POS(no,pos);
PRNT_BITS(c,SIZE)
}
