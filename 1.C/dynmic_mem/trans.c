#include<stdio.h>

#include<stdlib.h>
	
int **ptr,**t_mat;

void get_mat(int row,int col){

	int i,j;

	ptr = (int **) malloc(row*sizeof(int *));
	for(i=0;i<row;i++) 
		ptr[i] = (int *)malloc(col*sizeof(int));
	
	for(i=0;i<row;i++){
                printf("enter the row%d ele(%d): ",i+1,col);
                for(j=0;j<col;j++)
                scanf(" %d",&ptr[i][j]);
//              printf("\n");
        }
	printf("\n");
}

void tran_mat(void *p,int row,int col){

	int **a = p;
	int i,j;

	t_mat = (int **)malloc(col*sizeof(int*));
	for(i=0;i<col;i++) t_mat[i] = (int *)malloc(row*sizeof(int));
		
	for(i=0;i<col;i++)
		for(j=0;j<row;j++) 
				t_mat[i][j]=a[j][i];
	
}

void print_mat(void *p,int row,int col){

	int **a = p;
	int i,j;

	for(i=0;i<row;i++){
		printf("\t");
		for(j=0;j<col;j++){
			printf("%d\t",a[i][j]);
			}
	printf("\n");
}
	printf("\n");
}

main(){

	int row,col;
	printf("enter row,col:");
	scanf("%d%d",&row,&col);
	

	get_mat(row,col);
	printf("given mat:\n\n");
	print_mat(ptr,row,col);
	
	printf("transpose of the mat:\n\n");
	tran_mat(ptr,row,col);

	print_mat(t_mat,col,row);
}
