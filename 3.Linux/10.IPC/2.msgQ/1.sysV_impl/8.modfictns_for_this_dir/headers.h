#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY 12345

int len;

typedef struct msgbuf {
   
               long mtype;       
               char mtext[1000];    
	
               }msg;

 msg msgp;
