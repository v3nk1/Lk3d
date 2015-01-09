//w.a.p for storing 4 unsigned char in an unsigned integer. and read by a function as it is;

#include<stdio.h>
/*
unsigned int pchar(unsigned char a)
{

printf("%c",a);

}

int main()
{
unsigned int a;
unsigned char char1,l,k,j,h;
printf("char1(l) char2(k) char3(j) char4(h):");
scanf("%c%c%c%c",&l,&k,&j,&h);
printf("%d%d%d%d",l,k,j,h);
a=(k<<8)|(j<<16)|(h<<24)|l;
printf("%d",a);
printf("what char u want to read:");


scanf("%c",&char1);
printf("\n\n");
printf("%c",char1);

pchar(char1);
}
*/

unsigned char rd_ch(unsigned int a,int p)
{
	return ((a>>((4-p)*8))&0xff);
}
unsigned int wr_ch(unsigned int a,unsigned char  p)
{
static int  cnt=0;
if(cnt>=4) {
printf("no space\n");
return a;
}
if(cnt)
{cnt++;	return ( a=((a<<(8))|p));}
else
{cnt++;return ( a=(a^a)|p);}

}
main()
{
	unsigned int a;
	unsigned char ch;
	a=wr_ch(a,'A');
printf("%x\n",a);
	a=wr_ch(a,'B');
printf("%x\n",a);
	a=wr_ch(a,'C');
printf("%x\n",a);
	a=wr_ch(a,'D');
printf("%x\n",a);
	a=wr_ch(a,'F');
printf("%x\n",a);
ch=rd_ch(a,1);
printf("%c\n",ch);
ch=rd_ch(a,2);
printf("%c\n",ch);
ch=rd_ch(a,3);
printf("%c\n",ch);
ch=rd_ch(a,4);
printf("%c\n",ch);
}
