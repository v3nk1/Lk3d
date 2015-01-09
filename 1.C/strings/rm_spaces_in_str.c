#include<stdio.h>
#include<string.h>

void remove_sp(char *in,char *out){

	char tmp[strlen(in)+1],*p;
	strcpy(tmp,in);
	p=tmp;
/*	while(*in){
		if(*in==' '){
			in++;
			continue;
			}
		*out++=*in++;
	}
*/
	while(*p){
		if(*p==' '){
			p++;
			continue;
			}
		*in++=*p++;
	}
	*in='\0';
}

main(){

	char str[]="aA b c d e f";
	char tmp[100]={};
	
	remove_sp(str,tmp);

	printf("%s\n",str);
		
}
