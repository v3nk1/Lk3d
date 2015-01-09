#include<stdio.h>
void pos_find(int *p,int s,int ele){
int i=0;
for(;i<s;i++){
if(ele==*(p+i)){
 printf("pos is %d of that array:\n",i);
return;/////////////////////nahi toh executes for loop times..
}
}
printf("invalid ele\n");
}
main(){
int s,i,ele;
printf("enter no.. ele of array:");
scanf("%d",&s);
int a[s];
for(i=0;i<s;i++){
printf("enter ele%d:\n",i+1);
scanf(" %d",&a[i]);
}
printf("enter an ele u wnt 2 find pos:");
scanf("%d",&ele);
pos_find(a,s,ele);
}
