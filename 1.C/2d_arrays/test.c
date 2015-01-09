#include<stdio.h>
#include"array.h"
int r,co;
int c[r][co];
void sum_mat(void *a,void *b,int row,int col){
        //int (*x)[col]=a,(*y)[col]=b,(*c)[col],i,j;
        int (*x)[col]=a,(*y)[col]=b,i,j;
        for(i=0;i<row;i++){
                for(j=0;j<col;j++)  c[i][j]=x[i][j]+y[i][j];
//return c;
}
//print_mat(c,2,2);}
//return (c);
}

main(){
int row1,col1,row2,col2;
printf("enter row,col size of mat1:\n");
scanf("%d%d",&row1,&col1);
printf("enter row,col size of mat2:\n");
scanf("%d%d",&row2,&col2);
r=row1;
co=col1;
if(row1==row2 && col1==col2){
        int a[row1][col1],b[row1][col1];
        printf("enter mat1 ele:\n");
        read_mat(a,row1,col1);
        printf("enter mat2 ele:\n");
        read_mat(b,row1,col1);
        //int *c;
        sum_mat(a,b,row1,col1);
        print_mat(c,row1,col1);

}
else printf("invalid sizes\n");
}
