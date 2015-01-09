#include<stdio.h>
#include<string.h>

unsigned int my_atoi(char *str1){

	unsigned int i,dec=0;

	for(i=0;i<strlen(str1)/*6*/;i++){
		if(*(str1+i)<=57){

			dec=dec*10+(*(str1+i)&0x0f);  // think in hexa decimal concept..we can also do *(stt1+i)-48 or *(str1+i)-0x30;
			}
		
	if(*(str1+i)>57) return dec;

	}

	return dec;

}

main(){

	char str1[100];//="12AB7";
	printf("enter ascii: ");
	scanf(" %s",str1);
	unsigned int dec;
	//printf("%c%c",str1[0],str1[1]);
	//printf("\n%s",str1);
	dec=my_atoi(str1);
	printf("dec=%d\n",dec);

}
