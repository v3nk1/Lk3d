#include<stdio.h>
#include"queue.h"

main(){

	que_t q1,q2;//no need of create, by the time u create it u are creating a structure defined in "queue.h"

	que_init(&q1);
	que_init(&q2); //Here no need create any fucking instances of que_t, since we are not using the que what we hav passed to insert an element.. See enque() in "queue.h" we are just using start variable na..
	if(enque(&q1,1)==-1) errmsg("enque"); //pass NULL instead of &q1 also it will work..
/*	if(enque(&q1,2)==-1) errmsg("enque");
	if(enque(&q1,3)==-1) errmsg("enque");
	if(enque(&q1,4)==-1) errmsg("enque");
	if(enque(&q2,5)==-1) errmsg("enque");//q2 will also insert into the one que that was in "queue.h".
	if(enque(&q2,6)==-1) errmsg("enque");
	if(enque(&q2,7)==-1) errmsg("enque");
	if(enque(&q2,8)==-1) errmsg("enque");
	if(enque(&q2,9)==-1) errmsg("enque");
*/
	if(disp_que(q1)==-1) errmsg("disp_Q");//here we no need to send any que name..
	if(deque(q1)==-1) errmsg("deque");//for deque also no need to send any que name..

	if(disp_que(q2)==-1) errmsg("disp_Q");//it just displays the entire elements in the only one que(not our created que, its just displays predifined que in "queue.h" which is pointed by start..)

}
