//there is no predefined function for converting integer to ascii, ie., invert of atoi..

#include<stdio.h>
#include<string.h>

void my_i2a(char *char_num){

unsigned long int int_num,temp,divdent=1;
scanf("%ld",&int_num);
printf("readed=%ld\n",int_num);
if(int_num!=4196544){
int dig=1,i;
temp=int_num;
while(temp/=10) dig++, printf("dig=%d\n",dig); temp=dig;
while(--temp) divdent*=10;printf("dvdnt=%ld\n",divdent);
for(i=0;i<dig;i++){
	int x=(int_num/divdent);
	char_num[i]=x+48;
	int_num-=x*divdent;
	divdent/=10;
	printf("%c",char_num[i]);
	}
	char_num[i]='\0';
//printf("loop=%s\n",char_num);
}
else printf("invalid number");
}
main(){
//while(1){
printf("enter integer: ");
char char_num[987654];
my_i2a(char_num);

//scanf("%s",char_num);

//write(1,char_num,strlen(char_num));
printf("\n");}
//}
