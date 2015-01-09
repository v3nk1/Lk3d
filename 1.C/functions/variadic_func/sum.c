#include <stdarg.h>
#include <stdio.h>

int sum(int cnt, ...){

	va_list ap;/*arg ptr*/
	int i,arg,total=0;
	va_start(ap,cnt);
	for(i=0;i<cnt;i++){
		total+=va_arg(ap,int);
		}
	va_end(ap);
	return total;

}

main(){

	int cnt=10;/*num of integers sent to sum function*/
	printf("sum: %d\n",sum(cnt,1,2,3,4,5,6,7,8,9,10));

}
