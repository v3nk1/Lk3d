#include<stdio.h>

int _init(){
	
	printf("library loaded\n");

}

int _fini(){

	printf("unload library\n");

}

int add(int a,int b){
	
	return a+b;
}
