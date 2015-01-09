/* program to see whether the child is having same GLOBAL data copy of its parent.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int glob_data = 10;/*DATA SEGMENT*/
int glob_bss;/*BSS SEGMENT*/

main(){

	
	switch(fork()){

		case 0:/*childs context*/
			printf("in child glob_data =%d glob_bss =%d \n",glob_data,glob_bss);
			break;
		case -1:/*failure of fork()*/
			perror("fork");
			exit(1);
			break;
			
		default:/*parents context*/
			printf("in parent glob_data =%d glob_bss =%d \n",glob_data,glob_bss);
			break;
	}

}

	//OFCOURSE CHILD HAVING A COPY OF PARENT DATA(all segments);
