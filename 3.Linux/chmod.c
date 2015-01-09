//For any mode of opening or permission we use bitwiseor and bitwiseand operators.

#include<sys/stat.h>
#include<stdio.h>
main(int argc,char *argv[]){
chmod(argv[1],0664); // its is not possible to give *argv[2] as 2nd agrument to chmod, i.e., its impossible to give mode_t from command line argument, it doesnt throw any error but not give required results. since it u derefer argv[2] it just give base element only na..

//chmod("../char.c",S_IRUSR|S_IRGRP|S_IWGRP|S_IRWXO);
}

/*
0664 = rw-rw-r--  we can add ocatal value no need of bitwise oring octal numbers. see you want to give rw permissions to user then for read 400+ write 200=600, group also rw=040+020=060, others r only 004 total=600+060+004=664.
0777 = rwxrwxrwx  
0000 = ---------  

so for reading = 4
	write  = 2
	excute = 1
for user = 3rd digit from right to left
for group= 2nd digit from right to left
for other= 1st digit from right to left

*/

