/*
 * we can allocate memory for 2D array dynamically in two ways
 * 1. By creating row size of pointer of type int and looping row times and allocate memory by
 *    invoking malloc by column types

 * 2. 
 */

#include <stdio.h>
#include <stdlib.h>

main(){

	int row,col,i,j;

	printf("Enter row,col size: ");
	scanf("%d%d",&row,&col);

	int (*arr)[col]=malloc(row*col*sizeof(int));

	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			printf("Enter arr[%d][%d]: ",i,j),
			scanf(" %d",&arr[i][j]);

	for(i=0;i<row;i++){
		for(j=0;j<col;j++)
			printf("%d\t",arr[i][j]);
		printf("\n");
		}
	
}
