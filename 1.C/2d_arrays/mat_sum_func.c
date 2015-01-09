#include<stdio.h>
#include"array.h"
int *sum_mat(void *p,void *q,int row,int col){
int (*x)[col]=p,(*y)[col]=q,(*c)[col],i,j;//printf("%p\n",*c);
for(i=0;i<row;i++)for(j=0;j<col;j++) c[i][j]=x[i][j]+y[i][j];
return *c;
}
main(){
int a[3][3]={0,1,2,3,4,5,6,7,8};
int *c=sum_mat(a,a,3,3);
//printf("%lu %lu\n",sizeof (p),sizeof (q));
//printf("%p %p\n",);
print_mat(c,3,3);
}
