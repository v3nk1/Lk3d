

#include<stdio.h>

main(int count,char *ch[]){

	int i=0,sum=0;//int i=0;
	//while((i++<count-1)) 
	while(++i<count)
	{
	sum+=atoi(ch[i]); // here atoi is necessary since we are giving each as a string in command line argment ie., ./a.out 1 2 3.
//	printf("%s\n",ch[i]);
	}

printf("%d\n",sum);

}
