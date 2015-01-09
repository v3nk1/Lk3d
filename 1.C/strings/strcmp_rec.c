#include <stdio.h>

char strcmp_rec(char *str1,char *str2){

	char tmp=*str1-*str2;
	if(tmp || !*str1 || !*str2)
		return tmp;
	return strcmp_rec(++str1,++str2);
}

int main(){

	char str1[100],str2[100];

	printf("Enter string1: ");
	scanf("%[^\n]",str1);
	getchar();
	printf("Enter string2: ");
	scanf("%[^\n]",str2);
	
	printf("%d\n",strcmp_rec(str1,str2));
	return 0;
}
