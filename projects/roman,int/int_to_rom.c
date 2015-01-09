#include<stdio.h>
#include"ir.h"
#include<string.h>
int int_to_roman_check(int in){

	if(in<=0 || in>3999){
		printf("Invalid input\n");
		return -1;
		}

}

int int_to_roman(char *rom,int tmp){
	int i=0;
	if(int_to_roman_check(tmp)<0)
			return -1;
while(tmp){
	while(tmp>=1000){
		tmp-=1000;
		strcpy(strchr(rom,'\0'),int2roman(1000));
		}
	if(tmp>=900){
		tmp-=900;
		strcpy(strchr(rom,'\0'),int2roman(900));
		}
	while(tmp>=500){
		tmp-=500;
		strcpy(strchr(rom,'\0'),int2roman(500));
		}
	if(tmp>=400){
		tmp-=400;
		strcpy(strchr(rom,'\0'),int2roman(400));
			}
	while(tmp>=100){
		tmp-=100;
		strcpy(strchr(rom,'\0'),int2roman(100));
		}
	if(tmp>=90){
		tmp-=90;
		strcpy(strchr(rom,'\0'),int2roman(90));
		}
	while(tmp>=50){
		tmp-=50;
		strcpy(strchr(rom,'\0'),int2roman(50));
		}
	if(tmp>=40){
		tmp-=40;
		strcpy(strchr(rom,'\0'),int2roman(40));
		}

	while(tmp>=10){
		tmp-=10;
		strcpy(strchr(rom,'\0'),int2roman(10));
		}
	if(tmp>=9){
		tmp-=9;
		strcpy(strchr(rom,'\0'),int2roman(9));
		}
	if(tmp>=5){
		tmp-=5;
		strcpy(strchr(rom,'\0'),int2roman(5));
		}
	if(tmp>=4){
		tmp-=4;
		strcpy(strchr(rom,'\0'),int2roman(4));
		}	
	while(tmp>=1){
		tmp-=1;
		strcpy(strchr(rom,'\0'),int2roman(1));
		}

	}

}

main(){

	int in;
	char rom[15]={};
while(1){
	memset(rom,0,sizeof(rom));
	printf("Enter integer [1-3999]: ");
	scanf(" %d",&in);
	int_to_roman(rom,in);
	printf("ROMAN: %s\n",rom);
	}

return 0;
}
