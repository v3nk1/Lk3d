//sorting objects in an array of objects by using string length of the intialised string in that array.

#include<stdio.h>
struct a{
char ch[50];
}p[5]={"venkatehs","omkar","naresh","ab","dfg"};
void sort_obj(struct a *q){   //instead of q use again p here;segmentation fault?
int j,cnt=0;
for(j=0;j<sizeof(p)/sizeof(p[j].ch);j++){
int i;
for(i=0;i<sizeof(p)/sizeof(p[i].ch)-1;i++){//printf("%d\n",i);
if(strlen(q[i].ch)>strlen(q[i+1].ch)) {struct a obj; 
obj=q[i];q[i]=q[i+1];q[i+1]=obj;
//printf("%s\n",q[i].ch);
}
}/*cnt++;*/}}
main(){
sort_obj(p);
int i;
for(i=0;i<sizeof(p)/sizeof(p[i].ch);i++)
printf("%s\n",p[i].ch);

}
