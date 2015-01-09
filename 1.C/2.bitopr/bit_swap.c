//w.a.p to swap individual bits ie., last to first, not a nibble.ie 1st bit to 8 positon and 8th bit to 1st position. ie exchange bit positions 1<==>8 2<==>7 3<==>6 4<==>5;

#include<stdio.h>
unsigned char bit_swap(unsigned char a){
unsigned char x,y,z,temp=0,c=0,b=0b10000001;
int i;
for(i=0;i<=3;i++){
c=a&((b>>i)|(b<<i));
pb(c);
x=(0xf0&c)>>(7-(2*i));      // & with f0 is very imp for i=3 iteration. before 2 iterations in d shifting autometically d oppst nibble erasd;
y=(0x0f&c)<<(7-(2*i));
//pb(x);
//pb(y);
//printf("---------------------------------------------------\n");
c=x|y;            //c=(c>>(7-(2*i)))|(c<<(7-(2*i)));

temp=temp|c;

}
return temp;
}
main()
{
unsigned char a;
printf("enter a value:");
scanf("%d",&a);           // hw 2 avoid warning?
printf("%d\n",a);
pb(a);
a=bit_swap(a);
pb(a);
}

