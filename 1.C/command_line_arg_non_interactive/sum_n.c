#include<stdio.h>
#include<stdlib.h>

main(int count,char *ch[]){

	float sum=0;  //double sum=0;
	int i;
	for(i=1;i<count;i++) sum+=(float)atof(ch[i]); //remove typecast float it defaultly returns double.see man atof.
	printf("%f\n",sum);

}
