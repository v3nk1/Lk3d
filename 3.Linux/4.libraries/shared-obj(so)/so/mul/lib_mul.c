#include<stdio.h>

int _init(){
printf("lib is loaded\n");
}

int _fini(){
printf("lib is unloaded\n");

}

int mul(int a,int b){
return a*b;
}
