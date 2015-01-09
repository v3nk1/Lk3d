//Do's and Dont's
/*
 * In 64-bit:
   ----------
	- strcmp("12345","1234");
	  return 1,0,-1 if s1 > s2, s1==s2, s1<s2.
  	- str1[100] ="12345",str2[100] = "1234";
	  strcmp(str1,str2);
	  if any mis-match *s1-*s2 (decimal value) where mis match occured.
	  otherwise 0(perfect match).
 * In 32-bit:
   ----------
	- gcc strcmp.c -m32
	- strcmp("12345","1234");
          return 1,0,-1 if s1 > s2, s1==s2, s1<s2.

 */
#include<stdio.h>

main(){

	char str1[100] ="12345",str2[100] = "1234";
	int k=strcmp(str1,str2);
	printf("%d\n",k);
		//strcmp("venkatesh","venk"); //it wil cause problem, always returns 1 or -1 only
	printf("%d\n",strcmp("12345","1234"));

}
