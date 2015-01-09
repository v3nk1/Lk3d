#include<stdio.h>
#include<stdlib.h>
main(){
FILE *fp=fopen("test.file","w");
if(!fp) perror("fopen"),exit(1);
}
