#include<stdio.h>
unsigned int toggle(unsigned int a,int pos,int no_bits){
unsigned int temp=(((0xffffffff>>pos)<<(31-no_bits))>>(31-no_bits))<<pos;
temp=temp^a;
return temp;
}
main()
{
unsigned int a;
int pos,no_bits;
printf("enter a value:");
scanf("%d",&a);
printf("enter pos,no_bits:");
scanf("%d%d",&pos,&no_bits);
pb(a);
a=toggle(a,pos,no_bits);
pb(a);
}
