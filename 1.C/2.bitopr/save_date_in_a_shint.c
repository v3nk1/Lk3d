//w.a.p to write date/month/year in an unsigned short integer. and to read it by function as dd:mm:yyyy


#include<stdio.h>
unsigned int wr_date(unsigned short int a,unsigned int p){
static cnt=0;
if(cnt==1){
a=(a|(p<<5));cnt++;                       ////////////
return a;
}
if(cnt==2){
a=(a|(p<<9));cnt++;                        ////////////
return a;
}

else{
cnt++; a=p;
return a;
}
return a;
}

unsigned int print_date(unsigned short int a){
int c=((a&(0xf0<<1))>>5);
/*if(c<10){
printf("%d:0%d:20%d\n",(a&(0xffff>>11)),c,((a&(0xff00<<1))>>9));
}
else*/
printf("%02d:%02d:20%d\n",(a&(0xffff>>11)),c,((a&(0xff00<<1))>>9));  // here %02d is 1st took "00" and inserts the ie month value from left   to right ie here insted of 6, 06 will print. 
return a;
}
main()
{
unsigned short int a;

a=wr_date(a,13); 		   //date
printf("%d\n",a);
a=wr_date(a,6);  
printf("%d\n",a);            //month
a=wr_date(a,13);
printf("%d\n",a);	  	   //year
print_date(a);



}
