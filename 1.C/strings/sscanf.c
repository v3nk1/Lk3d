#include <stdio.h>

main(){

	char ch[]="0x19\n:0x07\n:0x1990\n";
	int day,mon,yr;
	//sscanf(ch,"0x%02x\n" ":" "0x%2x\n" ":" "0x%4x\n",&day,&mon,&yr);
	sscanf(ch,"0x%02x\n:" ,&day);
	sscanf(ch+6,"0x%02x\n:",&mon);
	sscanf(ch+12,"0x%4x\n",&yr);
	//sscanf(ch,"%d:%d:%d",&day,&mon,&yr);

	printf("%x-%x-%x\n",day,mon,yr);

}
