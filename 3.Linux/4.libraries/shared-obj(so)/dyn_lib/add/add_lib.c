#include<stdio.h>

int _init(){

printf("add func is loaded\n");
}

int _fini(){

printf("add func is unloaded\n");

}
int add(int x,int y){

	return x+y;
}
