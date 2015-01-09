//w.a.p for setting bits at a time 3 positions are given. 

#include<stdio.h>
/*int pb(unsigned int i)
{
int temp;
for(temp=31;temp>=0;temp--)
{
((1<<temp)&i)>=1?printf("1 "):printf("0 ");
}
printf("\n");
}
*/
main()
{
unsigned int a;
int i,j,k;
printf("enter a value:");
scanf("%d",&a);
printf("give the 3-pos's u want to set");
scanf("%d%d%d",&i,&j,&k);
pb(a);
a=a|(1<<i)|(1<<j)|(1<<k);

pb(a);
}
