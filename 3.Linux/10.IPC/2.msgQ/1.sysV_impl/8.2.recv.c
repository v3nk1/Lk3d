#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY 0x1234

typedef struct{
	long mtype;
	char mtext[4];
}msg;

int main()
{
	int qid;
	int i;
	msg m1,m2;
	qid=msgget(KEY,IPC_CREAT);
        printf("Waiting to recv..\n");
	i=msgrcv(qid,&m1,sizeof(m1.mtext),10,0);
        if(i<0)
        {
          perror("Error: ");
          printf("Error in recv\n");
          msgctl(qid,IPC_RMID,NULL);
          return;
          }
	printf("val returned %d\n",i);
	printf("%ld %s\n",m1.mtype,m1.mtext);

        printf("Waiting to recv..\n");
	i=msgrcv(qid,&m2,sizeof(m2.mtext),20,0);
        if(i<0)
        {
          perror("Error: ");
          printf("Error in recv\n");
          msgctl(qid,IPC_RMID,NULL);
          return;
          }
	printf("%ld %s \n",m2.mtype,m2.mtext);

        printf("DONE... :)\n");
	return 0;
}

