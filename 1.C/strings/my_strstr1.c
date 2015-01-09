//w.a.p to implement strstr by using strncmp. see here strNcmp makes task easier becoz it compares in specified length. strncmp retuns integer value which is d difference of missmatch char.

#include<string.h>
#include<stdio.h>

char *my_strstr(const char *str,char *srch){//we can catch a raw string in a char ptr i.e *srch OR instead we can use char array;
	char *s=str;
	int a;

/****************************************/
	while(*s){

		if(*s==*srch){
			if(!strncmp(s,srch,strlen(srch)))  //in strcmp we can use addresses or symbol name of strings as arguments. ie symbol name itself indicates base address of that char array.
				return s;
			else
		 		s++;
		}
		else
			s++;

	}

return NULL;              // return a NULL value.

}

/****************************************/
/*     
check:       
//if(*s++){
if((*s==*srch)){
while((*s++==*srch)){
printf("%c---- %c\n",*s,*srch);
      a=strncmp(s,srch,strlen(srch));
printf("%d\n",a);
       if(!a)  return s;
//       else goto check; 
 	
	      
}

  }else {s++; goto check;}
}   */

main(){

	char str[]="this is rainy here";
	//printf("%d\n",strncmp(str,"he",2));
	//my_strstr(str,"is");
	printf("%p\n",my_strstr(str,"abc"));

}
