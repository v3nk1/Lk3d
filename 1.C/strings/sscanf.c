#include <stdio.h>

main(){

	char *ch="19:07:1990";
	int day,mon,yr;

	sscanf(ch,"%d" ":" "%d" ":" "%d",&day,&mon,&yr);
	//sscanf(ch,"%d:%d:%d",&day,&mon,&yr);

	printf("%d-%d-%d\n",day,mon,yr);

}
