#include<stdio.h>
#include<stdlib.h>

int **ptr;

void get_mat(int row,int col){
	
	int i,j;
	ptr = (int **)malloc(row*sizeof(int *));
	
	for(i=0;i<row;i++)
		ptr[i]=(int *)malloc(col*sizeof(int));
	
	for(i=0;i<row;i++){
		printf("enter the row%d ele(%d): ",i+1,col);
		for(j=0;j<col;j++)
		scanf(" %d",&ptr[i][j]);
//		printf("\n");
	}
	printf("\n");		
}

void print_mat(void *a,int row, int col){

	int (*x)[col]= a,i,j;
	
	for(i=0;i<row;i++){
		for(j=0;j<col;j++)
		printf("%d\t",ptr[i][j]);
		printf("\n");
		}
	printf("\n");

}

main(){

	int row,col,i,j;
	printf("enter the rows,col: ");
	scanf("%d%d",&row,&col);
	
	get_mat(row,col);//need to allocate a global variable of type ptr to (ptr to int); (ie., int **).
	
	print_mat(ptr,row,col);

}
