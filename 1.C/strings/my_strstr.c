// w.a.p to implement strstr without using strlen and strNcmp functions.means u can use strcmp;


#include<stdio.h>

char *my_strstr(const char *str,char *srch){

	char *s=str; int a,cnt=0;
	//printf("%c\n",*s);

	while(*s){
	
		cnt++;     // observe d need of cnt carefully.. must required.
		if(*s==*srch){
			if(a=strcmp(s,srch)) 
				if( a==*(s+cnt)) return s;
			else return s;
			}
		else s++;

	}

return NULL;

}

main(){

	char str[]="this is rainy here";
	//printf("%s\n",str);
	//my_strstr(str,"is");

	printf("%s\n",my_strstr(str," "));

}

