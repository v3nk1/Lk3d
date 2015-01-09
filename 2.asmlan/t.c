#include<stdio.h>
int my_atoi(char *s){int sum=0;
while(*s){
if(*s>47&&*s<58) sum=sum*10+((*s)&0x0f);
else return sum;
s++;}return sum;}
main(){
//my_atoi("12b4");
printf("%d\n",my_atoi("12b4"));

}
