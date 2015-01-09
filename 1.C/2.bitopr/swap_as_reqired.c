// w.a.p to swap the no_bits from the given pos in given 2 integers.
#include<stdio.h>
void swap_bits(unsigned int a,unsigned int b,int pos,int no_bits,unsigned int *p,unsigned int *q){
unsigned int x,y;
unsigned int temp;
x=a>>pos; x=x<<(31-no_bits); x=x>>(31-no_bits); x=x<<pos;
//pb(x);
y=b>>pos; y=y<<(31-no_bits); y=y>>(31-no_bits); y=y<<pos;
//pb(y);

temp=0xffffffff>>pos;//pb(temp);
temp=temp<<(31-no_bits);//pb(temp); 
temp=temp>>(31-no_bits);//pb(temp);
temp=temp<<pos;//pb(temp);
temp=~temp;//pb(temp);

a=(a&temp)|y;//pb(a); // be sure that it is |y otherwise same value obtained.
b=(b&temp)|x;//pb(b);
*p=a;
*q=b;

}

main()
{
unsigned int a,b; int pos,no_bits;
while(1){
printf("enter the 2 integers u want to swap bits: ");
scanf("%d%d",&a,&b);       //dnt gv any space in scanf. since it will treat space also as a char. and enter the values in runtime by separating with space.
printf("enter the pos, no_bits: ");
scanf(" %d%d",&pos,&no_bits);
pb(a);
pb(b);
swap_bits(a,b,pos,no_bits,&a,&b);  //here i'm using ptr's in functns. i'm retuning 2 value of a,b at a time.
pb(a);
pb(b);
}}
