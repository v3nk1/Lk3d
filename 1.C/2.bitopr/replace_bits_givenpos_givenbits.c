//w.a.p to replace the bits in "a" with that of in "b". in the function we hav to pass the pos,no_bits ie we are passing nobits to replace where from.

#include<stdio.h>
int fun(unsigned int a,unsigned int b,int pos,int no_bits)
{
b=(b>>pos);
b=(b<<(32-no_bits));
b=b>>(32-no_bits);
b=b<<pos;
unsigned int temp;
temp=(0xffffffff>>pos);
temp=temp<<(32-no_bits);
temp=temp>>(32-no_bits);
temp=temp<<pos;
temp=~temp;
a=a&temp;
b=a|b;
return b;
}

int main()
{
unsigned int a,b;
printf("\nenter a,b values:");
scanf("%d%d",&a,&b);
int pos,no_bits;
printf("\nenter pos,no.. bits u want to replace:");
scanf("%d%d",&pos,&no_bits);
printf("a=");
pb(a);
printf("b=");
pb(b);
a=fun(a,b,pos,no_bits);
printf("a=");
pb(a);
printf("b=");
pb(b);
}
