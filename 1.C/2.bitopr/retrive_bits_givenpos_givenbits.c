//w.a.p for reading the bits from the given pos to no_bits;

#include<stdio.h>
int fun(unsigned int a,int pos,int no_bits)
{
a=(a>>pos);
a=(a<<(32-no_bits));
a=a>>(32-no_bits);
return a;
}

int main()
{
unsigned int a,b;
printf("enter a value");
scanf("%d",&a);
int pos,no_bits;
printf("enterpos,no.. bits u want to read");
scanf("%d%d",&pos,&no_bits);
pb(a);
b=fun(a,pos,no_bits);
pb(b);
}
