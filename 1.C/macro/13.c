//set date in a short integr and get date frm a short integer and print in date format. 

#include<stdio.h>

#define SET_DATE(day,mon,year) a=day|mon<<5|year<<9;
//#define GET_DATE(a) printf("%02d/%02d/20%d\n",(a<<11)>>11,(a<<7)>>12,(a>>9)); //To perform (a<<11)>>11 then assembler takes temparary register of size as word sizeof the archetecture. so here a is temp is unsigned int. temp=(a<<11)>>11 so same value appeared,so see treat as 4byte or assign it to a short integer.
#define GET_DATE(a) printf("%02d/%02d/20%d\n",(a<<27)>>27,(a<<23)>>28,(a>>9)); 

main(){

	int day,mon,year;
	unsigned short int a;

	printf("enter day mon year:");
	scanf(" %d%d%d",&day,&mon,&year);

	SET_DATE(day,mon,year)
	//printf("%d\n",a);
	GET_DATE(a)

}
