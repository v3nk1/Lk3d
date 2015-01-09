// geniric func to print 2d matrix w/o geniric(void) pointers

#include<stdio.h>
int row,col;

void print_mat(int (*p)[col]){
	int i,j;
	for(i=0;i<row;i++)for(j=0;j<col;j++) printf("%d\t",p[i][j]);
	printf("\n");
}

main(){
	printf("enter row,col:");
	scanf("%d%d",&row,&col);
	int a[2][2]={1,2,3,4}
	print_mat(a);
}
