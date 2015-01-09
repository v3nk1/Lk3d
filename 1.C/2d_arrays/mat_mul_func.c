NOT WORKINGGGGGGG

#include<stdio.h>
#include"array.h"
int* mat_mul(void *p,void *q,int row1,int col1,int row2,int col2){
int (*x)[col1]=p,(*y)[col2]=q,cc[row1][col2],(*c)[col2]=cc,i,j,k,sum; //if u intialise j=0 here the j loop just execute 1 iteration only.
for(i=0;i<row1;i++){
	for(j=0;j<col2;j++){
	
		sum=0; 
		for(k=0;k<col1;k++){ sum+=x[i][k]*y[k][j];}
printf("%d %d %d %d\n",i,j,k,sum);
	cc[i][j]=sum;
}}
return *cc;
}
main(){
int row1=3,col1=3,row2=3,col2=3;
//printf("enter row,col size of mat1:\n");
//scanf("%d%d",&row1,&col1);
//printf("enter row,col size of mat2:\n");
//scanf("%d%d",&row2,&col2);

if(col1==row2){
	
        int a[3][3]={1,0,0,0,1,0,0,0,1},b[3][3]={1,2,3,4,5,6,7,8,9};
	
    /*    printf("enter mat1 ele:\n");
        read_mat(a,row1,col1);
        printf("enter mat2 ele:\n");
        read_mat(b,row2,col2);                      */
      // mat_mul(a,b,row1,col1,row2,col2);
       // print_mat(c,row1,col2);
/*printf("1st mat:\n");
print_mat(a,row1,col1);
printf("\n");
printf("2nd mat:\n");
print_mat(b,row2,col2);
printf("\n");*/
      int *c= mat_mul(a,b,row1,col1,row2,col2);
       print_mat(c,row1,col2);

}
else printf("invalid sizes\n");
}
