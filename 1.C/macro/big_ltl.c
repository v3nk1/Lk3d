#include<stdio.h>
#define LTL_BIG(a) char *p=(char *)&a,*q=(char *)&b,i;q+=SIZE-1;for(i=0;i<SIZE;i++) *q--=*p++;
#define SIZE sizeof(a)
#define PRNT_HEX(b) printf("%x\n",b);
main(){
unsigned int a=0xaabbccdd,b;
LTL_BIG(a)
PRNT_HEX(b)
}
