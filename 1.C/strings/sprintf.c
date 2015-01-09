#include <stdio.h>

main(){

	int day=19,mon=7,yr=1990;
	char ch[100];
	
	sprintf(ch,"%d:%02d:%d",day,mon,yr);
//	sprintf(ch,"%d:0%d:%d",day,mon,yr);
	printf("%s\n",ch);

}
