#include<stdio.h>
#include"ir.h"
#include<string.h>

int valid_roman(char romn){

	switch(romn){

		case 'M':case 'D':case 'C':case 'L':case 'X':case 'V':case 'I':
			return 0;
		default:
			return -1;
	}

}

int roman_to_int_check(char *str){

	while(*str){
		if(valid_roman(*str)<0){
			printf("Enter a valid roman word\n");
			return -1;
			}
		str++;
		}
	return 0;
}

int comp_val(char a,char b){

	if(roman2int(a)>=roman2int(b)) return roman2int(a);
	else return -roman2int(a);

}

int roman_to_int(char *str){
	int val=0;
	if(roman_to_int_check(str)<0)
		return -1;
	while(*str){
		val+=comp_val(str[0],str[1]);
		str++;
		}
	return val;
}

main(){

char str[20];
printf("Enter ROMAN value: ");
scanf(" %s",str);
printf("%d\n",roman_to_int(str));

return 0;
}
