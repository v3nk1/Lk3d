//w.a.p to clear the bits at a time 3 positions are given.

#include<stdio.h>
main()
{
unsigned int a;
int i,j,k;
printf("enter a value:");
scanf("%d",&a);
printf("give the 3-pos's u want to set");
scanf("%d%d%d",&i,&j,&k);
pb(a);
a=a&~((1<<i)|(1<<j)|(1<<k));                          

pb(a);
}
