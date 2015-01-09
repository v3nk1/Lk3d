#include<stdio.h>
int *add(int (*a)[2],int (*b)[2]){int i,j,*p;int c[2][2];
for(i=0;i<2;i++)
	for(j=0;j<2;j++){
	//a[i][j]+b[i][j];
	c[i][j]=a[i][j]+b[i][j];
	     printf("%d ",c[i][j]);
	}return c; }
main(){
	int a[2][2]={{1,2},{3,4}};
	int b[2][2]={{1,2},{3,4}},i,j;
	int (*sum)[2]=add(a,b);
		   //for(i=0;i<2;i++)
		   //   for(j=0;j<2;j++){
	           //  printf("%d ",sum[i][j]);}
	           //	printf("\n");

}

