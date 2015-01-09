//ftok is the funtion used to generate an unique "key" for the given file name(path) and an unique integer

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

main(){

	key_t key;

	key = ftok("/tmp/temp",10); //give the path as "/tmp" or "/var" these are ment to temparory creations.. Before u invoke it (the given file(empty) shud be there in the specified path)use create the filel in that path by using "touch"(touch creates an empty file) command in shell prompt..

	if(key==-1) perror("ftok"),exit(1);

	printf("key: %lu\n",key);

}

/********************************************************************************************************************************

NOTES:

"ftok" generates a unique key by using path(where it resides including filename), and project id(some no);
	if these 2 are same then u how many times u invoke ftok function it will return same key;
	if file name or proj id changed (we can say any one of them is changed then the key generate is changed), So for each set of arguments(arg1,arg2 of ftok) u are passing those will have their own unique key..

*********************************************************************************************************************************/
