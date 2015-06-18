//to receive a sent msg..

#include"./headers.h"

main(int argc, char *argv[])
{

	int msqid = msgget(KEY, IPC_CREAT);	//opening a specif mesgQ by its unique key given by me in header file

	struct msqid_ds buf;
	msgctl(msqid, IPC_STAT, &buf);
	printf("Num of msgs in the specified Q: %u\n", buf.msg_qnum);

	int k = 0;
	unsigned long int size =
	    msgrcv(msqid, &msgp, 1000, k, IPC_NOWAIT | MSG_NOERROR);

/*3rd arg: i passed 3rd arg as 1000(max num i defined in the sructure), but becoz of i passed MSG_NOERROR then it will take care 	     of rounding off to the data size*/

	/*4th arg*///if k=0 then there is no order of reading.. first in first out..
	//if k=123(some specified value) then it will try to read the mtype = 123(as specified num) msg only, if              there is an mtype then it will read otherwise "no such type of msg as desired" will displayed.

	if (size == -1)
		perror("msgrcv"), exit(1);

	printf("%lu bytes red(read)\n", size);
	printf("read data:\n\t%s\n", msgp.mtext);

}
