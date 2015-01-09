#include<stdio.h>
#include<stdlib.h>
main(int block,int *ptr,int i){
printf("enter d no of ele:\n");
scanf("%d",&block);
ptr=(int *)calloc(block,4);
printf("enter ele:\n");
for(i=0;i<block;i++)
//scanf(" %d",ptr+i);
for(i=0;i<block;i++)
printf("%d ",*(ptr+i));
}
