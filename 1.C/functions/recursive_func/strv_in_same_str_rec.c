/*
 * Here actually u are pushing the address into stack(not particular char values) 
 * So what i wanna tell is as u are updating the h in v, 
 * it actually update in that particular address.
 * So half of the values will go correctly. After that we are going to 
 * populate what we hav poplutated earlier.
 * In bellow case takkat, to overcome this we will swap values within a half loop, 
 * make sure u are running loop half times only..
 */


#include<stdio.h>

void str_rev(char *str){

	static char swp;
	static i;

//	printf("***: %s\n",str);
	if(*(str+1)){
		i++;
		str_rev(str+1);
		}

//	printf("%c\n",*(str-i));
	
if(i/2){/*As we are doin swping,It shud be done only for half times only*/
	swp=*(str-i);
	*(str-i)=*str;
//	printf("b4: %c\n",*str);
	*str=swp;
//	printf("aftr: %c%c%c%c%c%c%c****%c\n",str[0],str[1],str[2],str[3],str[4],str[5],str[6],*(str-i));
//	printf("%i | %c | %c\n",i,str[-i],*str);
//	printf("%s\n",str);
	i=i-2;
	}
}

main(){

	char str[]="venkatesh";

	printf("original: %s\n",str);
	str_rev(str);
	printf("reverse : %s\n",str);

}
