//w.a.p for calculating the sum of the individual digits of entered decimal num;
#include<stdio.h>
int sum_dig(unsigned int a){
unsigned int b=0;
int i;
for(i=0;i<=7;i++){
//pb((a>>(4*i))&0xf);

b= b+((a>>(4*i))&0xf); //without last bracket out will be wrong.
//printf("%d\n",b);
}
return b;
}

main()
{
unsigned int a;
printf("enter value:\n");
scanf("%x",&a);
//printf("%x\n",a);
//pb(a);

a=sum_dig(a);    // here a value is replaced by sum of individual digs. u dont want it declare another variable.
printf("individual dig sum:%d\n",a);
}
