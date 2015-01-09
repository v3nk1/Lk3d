#include<stdio.h>
struct my{
char s[25];
int a[15];
}o1={"learn asm",{1,4,3}},o2={"read lang",{3,1,4}};
void swap(struct my *o1,struct my *o2){
struct my temp=*o1; *o1=*o2; *o2=temp;   //we cannt assign two structure objcts of diff type;ie we can if& only if the stucture objects has defined under same tag name.
}
main(){
swap(&o1,&o2);
printf("%s == %d\n",o1.s,o1.a[0]);
printf("%s == %d\n",o2.s,o2.a[0]);

}
