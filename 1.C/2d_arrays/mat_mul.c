//HERE U'VE TO GIVE THE RESULTANT ARRAY SIZE GLOBALLY..

#include<stdio.h>
#include"array.h"

int c[4][4];

void mat_mul(void *p,void *q,int row1,int col1,int row2,int col2){
int (*x)[col1]=p,(*y)[col2]=q,i,j,k; //if u intialise j=0 here the j loop just execute 1 iteration only.
for(i=0;i<row1;i++){ //int sum=0;
	for(j=0;j<col2;j++){int sum=0;  
		for(k=0;k<col1;k++) // printf("%d %d %d\n",i,j,k);
	        sum+=x[i][k]*y[k][j];
                c[i][j]=sum;
//printf("%d\n",sum);}
}}}
main(){
int row1=4,col1=4,row2=4,col2=4;
//printf("enter row,col size of mat1:\n");
//scanf("%d%d",&row1,&col1);
//printf("enter row,col size of mat2:\n");
//scanf("%d%d",&row2,&col2);

if(col1==row2){
//	int a[2][2]={1,0,0,1},b[2][2]={1,2,3,4};
//      int a[3][3]={1,0,0,0,1,0,0,0,1},b[3][3]={1,2,3,4,5,6,7,8,9};
	int a[4][4]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},b[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        mat_mul(a,b,row1,col1,row2,col2);
       print_mat(c,row1,col2);

}
else printf("invalid sizes\n");
}
