#include<stdio.h>
struct abc{
int a[100];
}o1={1,2,3},o2={1,2,3},o3; 
void add_obj(struct abc oo1,struct abc oo2,struct abc *oo3){
int i,x[sizeof oo1/sizeof (int)];
for(i=0;i<sizeof oo1/sizeof (int);i++){
x[i]=oo1.a[i]+oo2.a[i];
oo3->a[i]=x[i];  //here we are doin oo3=address;*oo3=o3; so (*oo3).a[i] means oo3->a[i] assigning it to direcly;
//int x[100];x[0]=oo1.a[0]+oo2.a[0];
}
//printf("%d %d %d\n",oo3->a[0],oo3->a[1],oo3->a[2]);

}
main(){
add_obj(o1,o2,&o3); // we cannt add two structure objects direcly. so we are doin it internally by size of member using loops.
printf("%d %d %d\n",o3.a[0],o3.a[1],o3.a[2]);
}


