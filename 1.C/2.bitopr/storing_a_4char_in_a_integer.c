//w.a.p for storing 4 unsigned char in an unsigned integer. and read by a function as it is;

#include<stdio.h>
unsigned int wr_ch(unsigned int a, unsigned char p)
{
static int cnt=0;
if(cnt>=4){
printf("no space to store");
return a;
}
if(cnt){
cnt++; return a=((a<<8)|p);
}
else{
cnt++; return a=p;
}
}
unsigned char rd_ch(unsigned int a, unsigned char p)
{
if(p>=5){
printf("error in byte");
return a;
}
return a=(a>>(8*(4-p))&0xff);
}

int main()
{
unsigned int a;
unsigned char ch;
int i;
unsigned char j;
for(i=0;i<=3;i++)
	{
	printf("enter char\n");
	scanf(" %c",&ch);
	wr_ch(a,ch);
	}

printf("what byte u want to read");
scanf("%d",&j);

rd_ch(a,j);

printf("%c\n",a);
}
