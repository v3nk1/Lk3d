/*give something along with a.out when u run the executable(a.out).
	EX: ./a.out venkatesh 12345
*/
#include<stdio.h>

main(int a,char *c[]){

	int i;

	printf("count:(argc) = %d\n",a);

	for(i=0;i<a;i++) printf("argv[i] = %s\n",c[i]);

}

/**********************************************************************
NOTES:
`````	(1).See here the concept is command line arguments, means when u run a particular executable on shell prompt along with the executable if u pass some vales(intgr or char constants) or string constensts, then those inputs are taken by the program what u hav writen as command line program..
	(2).Command-line arguments are two which are declared as arguments of main() function; those are argc,argv;
	
		(i).  Here argc is a integer type which will represent count of the passed argumets when u executing(run) in the shell prompt including "./a.out".
		(ii). And argv is a array of pointer to char:
			so the point is U PASS ANY THING TO COMMANDLINE ARGUMENT THE PASSED ENTITIES ARE TREATED AS POINTER TO 				STRING only..
			The base address is stored in the array of ptr to char as:
					argv[0] = in this the base address of "./a.out" is stored;
					argv[1] = in this the base address of "venkatesh" is stored;
					argv[2] = in this the base address of "12345" is stored; //note that here addresses are stored that why when u give direct address to printf and uses %s to print these are worked.. How this will be stored in memory? It is stored like we do have 0 to 9 characters na.. its treat each digit as a char data type stores in memory, like 1 will be stored in 1st byte, and 2 will be stored in 2nd byte and 3 will be stored in 3rd byte and 4 will be stored in 4th byte and 5 will be stored in 5th byte, NOTICE THAT FOR ACTUAL INTEGER 4BYTES ARE SUFFICIENT TO STORE THIS 12345, BUT HERE IT TAKES 5.. SO ITS NOT AN INTGER ANYMORE..
					this argv[2] is not an integer mind it;
				to make that integer we have to convert it into ascii to int
				there are some predefined functions to do that.. see man pages of bellow
					see man atoi
					see man atoil
					see man strtoul

*************************************************************************************************/
