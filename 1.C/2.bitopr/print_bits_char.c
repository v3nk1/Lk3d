#include<stdio.h>
unsigned char pb(unsigned char i)
{
int x,temp;
for(temp=7;temp>=0;temp--)
{
x=(i&(1<<temp));
(x>=1) ? printf("1 "):printf("0 ");
}
printf("\n");
return x;             // no need 2 return x?
}                             


