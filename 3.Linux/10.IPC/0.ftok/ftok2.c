//ftok is the funtion used to generate an unique "key" for the given file name(path) and an unique integer

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

main(){

	key_t key;

	key = ftok("/tmp/temp",10); //give the path as "/tmp" or "/var" these are ment to temparory creations.. Before u invoke it (the given file(empty) shud be there in the specified path)use create the filel in that path by using "touch"(touch creates an empty file) command in shell prompt..

	if(key==-1) perror("ftok"),exit(1);
	printf("key: %lu\n",key);

	key = ftok("/tmp/temp",10);
	if(key==-1) perror("ftok"),exit(2);
	printf("key: %lu\n",key);

	key = ftok("/tmp/temp2",10);
	if(key==-1) perror("ftok"),exit(3);
	printf("key: %lu\n",key);
	
	key = ftok("/tmp/temp3",10);
	if(key==-1) perror("ftok"),exit(4);
	printf("key: %lu\n",key);
	

}
