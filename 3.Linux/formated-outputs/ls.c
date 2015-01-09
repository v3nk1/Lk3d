#include<stdio.h>
main(){

	char arr[1234]="time:12/13/14";
	int date,mon,yr;
	
	sscanf(arr,"time: %d/%d/%d",&date,&mon,&yr);
//	sscanf(arr,"%d/%d/%d",&date,&mon,&yr);
//	sscanf(arr,"%d/%d/%d",&date,&mon,&yr);
	printf("%d %d %d\n",date,mon,yr);

}
