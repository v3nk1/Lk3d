// ITS USER INTERFACE (main)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"headers.h"

main(){
	prnt_num_of_rec();
	int i;
	menu();
	char code;
	printf("\nenter code:");
	scanf(" %c",&code);

if(code=='w' ||code=='W') write_fresh();

if(code=='d'||code=='D') del();
if(code=='a'||code=='A') add();
if(code=='m'||code=='M') modify();
if(code=='r'||code=='R') read();
}
