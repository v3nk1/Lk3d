#include<stdio.h>
#define SWP_BYTE(no) no<<8|no>>8
#define PRNT_BITS(c,SIZE) int i=SIZE *8 -1;for(;i>=0;i--) printf("%d ",c>>i&1);printf("\n");
#define SIZE sizeof(no)
main(){
unsigned short int  no=15,c;
c=SWP_BYTE(no);
PRNT_BITS(c,SIZE)
}
