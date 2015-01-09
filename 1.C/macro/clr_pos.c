#include<stdio.h>
#define CLR_POS(no,pos) no&~(1<<pos) //dont put ! instead of ~
#define PRNT_BITS(c) int i=31;for(;i>=0;i--) printf("%d ",c>>i&1);printf("\n"); //here u must put no|1<<pos insteadof SET_POS(no,pos)
main(){
unsigned int no=10,pos=1,c;
c=CLR_POS(no,pos);
PRNT_BITS(c)
}

