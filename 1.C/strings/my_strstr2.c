// w.a.p to implement strstr without using strlen and strNcmp functions.


#include<stdio.h>

char *my_strstr(const char *str,char *srch){
	
	char *s=str; //ikkada temp ptr type teskunte not working? & if u declare int i=0; here then i value is not  going to zero for each iteration of [2nd while],so we are declared temp[strlen()] and we used to store more than specified size of the array in the temp if strcmp!=0 so, if we declare in if condition after every iteration i=0;"GHAJINI"

	while(*s){
		if(*s==*srch){
			char temp[strlen(srch)];
			int i=0;
	
		while((i++)!=strlen(srch)){
			(*temp++=*s++);
			/*printf("%c\n",temp[i]);*/
			/*temp[i+1]='\0';i++;*/
			}
			//temp[i++]='\0' not working why?

			if(!strcmp(temp,srch))  return s;

			else s++;
		}
		else 
			s++;
	}

return NULL;

}

main(){

	char str[]="thi is rainy here";
	//printf("%s\n",str);
	//my_strstr(str,"is");

	printf("%s\n",my_strstr(str," h"));

}
