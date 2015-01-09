#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

void pop_arr(int **ptr,int row,int col){

	int i,j;
	srand(getpid());
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			ptr[i][j] = rand()%101;

}

void print_arr(int **ptr,int row,int col){

	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++)
			printf("%d\t",ptr[i][j]);
		printf("\n\n");
		}

}

main(){

	int row,col,i;
	printf("Enter row,col: ");
	scanf(" %d%d",&row,&col);
	int **ptr = malloc(sizeof(int*)*row);

	for(i=0;i<row;i++)
		ptr[i]=malloc(sizeof(int)*col);
	
	pop_arr(ptr,row,col);
	print_arr(ptr,row,col);

	for(i=0;i<row;i++)
		free(ptr[i]);

	free(ptr);

}
