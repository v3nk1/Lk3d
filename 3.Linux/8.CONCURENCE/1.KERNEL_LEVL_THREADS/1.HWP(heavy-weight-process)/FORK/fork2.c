/* its not known that when child executes or when parent will executes.. its purely up to the cpu schedular

	it wil be in random time, ./a.out > log and see the log
*/

#include<stdio.h>
#include<unistd.h>

main(){
	
	pid_t pid = fork();
	
	switch(pid){

		case 0: 
			printf("its in childs context\n");
		/*1*/	getchar();  //if "1" only opened, 2 in comments then execution completed after that it will be wait and press ENTER or ANY OTHER ASCII then child will its "end of program". after it prints "end of program" second time it seems to be waiting but it already comes to ur shell promts its waits for command only(program terminated it self ater second printf);
			break;

		default:
			printf("its in parents context\n");
		/*2*/	//getchar();
			break;
		}
	printf("end of program\n"); // it will be executed by both child and parent. sometimes after termination also it will execute dont be hurry(be patient and wait).
}
