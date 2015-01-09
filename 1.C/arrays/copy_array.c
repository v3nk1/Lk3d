#include<stdio.h>
void *cpy_array(int *dest,int *src,int s){  // we here directly update the source values in dest.
int *ret=dest;
int i=0;
for(;i<s;i++){
*dest++=*src++;
}
return ret;               // here no need to return it to fn...
}
main(){
int s,i;
printf("enter no.. ele of array:");
scanf("%d",&s);
int *dst,src[s],dest[s];
for(i=0;i<s;i++){
printf("enter ele%d:\n",i+1);
scanf(" %d",&src[i]);
}

dst=cpy_array(dest,src,s); 
for(i=0;i<s;i++) {
//*(dest+i)=*(dst+i);      //   *dest++=*dst++;

printf("%d ",dest[i]);     //printf("%d ",*(dest+i));
}
}
