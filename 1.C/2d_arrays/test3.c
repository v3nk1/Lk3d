#include<stdio.h>
main(){
int a[2][3];
printf("%u %u %u %u\n",sizeof(a),sizeof(a+10),sizeof(&a),sizeof(&a+1));
}
