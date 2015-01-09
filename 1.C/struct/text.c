#include<stdio.h>

main(){

struct stu {

	int a;
	char ch;
	char chs[100];

	}o[2];

int i;

for(i=0;i<2;i++)
	scanf(" %d %c %s",&o[i].a,&o[i].ch,o[i].chs);

for(i=0;i<2;i++)
	printf("%d %c %s\n",o[i].a,o[i].ch,o[i].chs);

}
