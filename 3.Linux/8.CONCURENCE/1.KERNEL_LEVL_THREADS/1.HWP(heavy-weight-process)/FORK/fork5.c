/* program to see whether the child is having same DYNMIC MEM ALLOC copy of its parent.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h> //for memset()
#include<stdlib.h>// for malloc()

main(){

	int *ptr = malloc(10*4);
	memset(ptr,9,40);
		/* 	Dont pass address of ptr (its a possible mistake). jst pass ptr, since in ptr holded address only we want 			to have 9's, then 
			it fillups the each byte with 9. so while reading 4 bytes at a time u'll got 151587081(ofcourse it true).
				Becoz while u reading interger 1by1 in hexa(09090909)=dec(151587081).
				
		*/	
	int i;
	
	switch(fork()){

		case 0:
			//childs context
			printf("in child:\n");
			for(i=0;i<=9;i++) printf("ptr[%d]= %d\n",i,ptr[i]);
			break;
		case -1:
			//failure of fork()
			perror("fork");
			exit(1);
			break;
			
		default:
			//parents context
			printf("in parent:\n");
			for(i=0;i<=9;i++) printf("ptr[%d]= %d\n",i,ptr[i]);
			break;
	}

}

	//OFCOURSE CHILD HAVING A COPY OF PARENT DATA(all segments);
