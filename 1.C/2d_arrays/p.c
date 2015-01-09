#include<stdio.h>

void print_mat(void *p,int row,int col){
        int (*q)[col]=p,i,j;
        for(i=0;i<row;i++){
                for(j=0;j<col;j++) printf("%d\t",q[i][j]);
        printf("\n");
        }
}
void read_mat(void *p,int row,int col){
	int (*a)[col]=p,i,j;
        //int row,col,i,j;
        //printf("enter array size [row][col]\n");
        // scanf("%d%d",&row,&col);
        //int a[row][col];
        //printf("enter d 1st row ele's:\n");
        for(i=0;i<row;i++){
                printf("enter d %drow ele's:\n",i+1);
                for(j=0;j<col;j++) scanf(" %d",&a[i][j]);
        }
//return *a;
}

main(){
int row,col;
printf("enter array size [row][col]:\n");
scanf("%d%d",&row,&col);

int a[row][col];
read_mat(a,row,col);
print_mat(a,row,col);
}
