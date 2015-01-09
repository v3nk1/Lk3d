#include<stdio.h>
#include<stdlib.h>
int cnt;
int *ptr;

prime(int min,int max){
	int i,j,prm;
	cnt=0;
 for(i=min;i<=max;i++){
	prm=0;
	for(j=1;j<=i;j++){
		!(i%j) ? prm++:0;
		}
	if(prm==2) {
		cnt++;
		ptr=(int *)realloc(ptr,cnt*sizeof(int));
		ptr[cnt-1]=i;
	}
}
}
main(){
	ptr=(int *)malloc(1*4);
	int min,max,i;
	scanf("%d%d",&min,&max);
	prime(min,max);
	for(i=0;i<cnt;i++)
		printf("%d ",ptr[i]);
}
