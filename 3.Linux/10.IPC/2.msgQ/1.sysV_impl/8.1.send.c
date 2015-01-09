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

main(){
	int qid;
	int i;
	msg m1,m2;
	qid=msgget(KEY,IPC_CREAT);
	m1.mtype=10;
	for(i=0;i<3;i++)
		m1.mtext[i]='a';
		m1.mtext[i]='\0';
	m2.mtype=20;
	for(i=0;i<3;i++)
		m2.mtext[i]='b';

		m2.mtext[i]='\0';
	


	i=msgsnd(qid,&m1,sizeof(m1.mtext),0);
	printf("return value of msgsnd of as=%d\n",i);
	getchar();
	i=msgsnd(qid,&m2,sizeof(m2.mtext),0);
	printf("return value of msgsnd of bs=%d\n",i);
/*
	getchar();
	m2.mtype=30;
        for(i=0;i<3;i++)
                m2.mtext[i]='c';

        i=msgsnd(qid,&m2,sizeof(m2.mtext),0);
        printf("return value of msgsnd of bs=%d\n",i);

*/

}	
