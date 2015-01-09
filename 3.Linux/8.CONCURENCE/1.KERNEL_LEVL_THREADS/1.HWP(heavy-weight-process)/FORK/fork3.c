/* program to see whether the child is having same local data copy of its parent.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

main(){

	int local = 10; /*STACK SEGMENT*/
	
	switch(fork()){

		case 0:/*childs context*/
			printf("in child local =%d\n",local);
			break;
		case -1:/*failure of fork()*/
			perror("fork");
			exit(1);
			break;
			
		default:/*parents context*/
			printf("in parent local =%d\n",local);
			break;
	}

}

	//OFCOURSE CHILD HAVING A COPY OF PARENT DATA(all segments).
