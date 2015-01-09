// Normally compile it.         

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include"msg.h"
#include"list.h"
#include<arpa/inet.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>

void * threadFunc(void *);

char smname[20], check[100], cmname[20], uname[20], cmd[5];
int snd, msg, sfd,cfd;

int
main ()
{

  int rd;
  socklen_t len;
  struct sockaddr_in saddr, claddr;

  sfd = socket (AF_INET, SOCK_STREAM, 0);
  if (sfd == -1)
    {
      perror ("socket");
      exit (2);
    }

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons (8888);

  if (bind (sfd, (struct sockaddr *) &saddr, sizeof (saddr)) < 0)
    {
      perror ("bind");
      return;
    }

  listen (sfd, 5);
  len = sizeof (struct sockaddr_in);
  printf ("Enter servername: ");
  scanf (" %s", smname);
  printf ("Waiting for clients..\n");

  while (1)
    {

      cfd = accept (sfd, (struct sockaddr *) &claddr, &len);
      if (cfd < 0)
	{
	  perror ("accept");
	  return;
	}

      printf ("Client connecting..\n");
      rd = recv (cfd, cmd, sizeof (cmd), 0);

      if (!rd)
	{
	  printf ("Client terminated by user\n");
	  continue;
	}
      else if (rd < 0)
	{
	  perror ("recv");
	  continue;
	}

      if (!strcmp (cmd, SRVCHK))
	{
	  send (cfd, smname, sizeof (smname), 0);
	  recv (cfd, cmd, sizeof (cmd), 0);
	  if (!strcmp (cmd, ILGCLI))
	    {
	      printf ("Denied: An unregisterd client\n");
	      continue;
	    }
	}
      pthread_t pid;
      pthread_create (&pid, NULL, threadFunc,&pid);

    }
  return 0;
}

void *
threadFunc (void *arg)
{
int i,cfdt=cfd,rd;
  sercli_t cbuff;

  while (1)
    {
      memset (&cbuff, 0, sizeof (cbuff));
      rd = recv (cfdt, cmd, sizeof (cmd), 0);
      if (!rd)
	{
	  printf ("A client terminatd by user\n");
	  pthread_exit(NULL);
	}
      else if (rd < 0)
	{
	  perror ("recv");
	  continue;
	}

      if (!strcmp (cmd, REG))
	{
	  recv (cfdt, cmname, sizeof (cmname), 0);
	  if(insert(&start,cmname)<0){
		send(cfdt,NOK,sizeof(NOK),0);
		continue;
		}
	  else {
		send(cfdt,OK,sizeof(OK),0);
		}
	  printf ("%s: Registerd\n", cmname);
	}
      else if (!strcmp (cmd, DREG))
	{
	  recv (cfdt, cmname, sizeof (cmname), 0);
	  if(del_ele(&start,cmname)<0){
		send(cfdt,NOK,sizeof(NOK),0);
		continue;
		}
	  else {
		send(cfdt,OK,sizeof(OK),0);
		}
	  
	  printf ("%s: Deregstrd\n", cmname);
	}
      else if (!strcmp (cmd, SND))
	{
	recv(cfdt,cmname,sizeof(cmname),0);
	que_t *qwe=search(&start,cmname);
	while(qwe->lck);
	qwe->lck=1;
	sprintf(INT,"%d",qwe->msgcnt);
	send(cfdt,INT,sizeof(INT),0);
	  for (i = 0; i < qwe->msgcnt ; i++)
	    {
	     
	      strcpy (cbuff.sndr,qwe->buff+qwe->snd);
//printf("%s\n",cbuff.sndr);
	      qwe->snd += (strlen(cbuff.sndr)+1);
	      strcpy (cbuff.subjct,qwe->buff+qwe->snd);
//printf("%s\n",cbuff.subjct);
	      qwe->snd += (strlen(cbuff.subjct)+1);
	      strcpy (cbuff.msg,qwe->buff+qwe->snd);
//printf("%s\n",cbuff.msg);
	      qwe->snd += (strlen(cbuff.msg)+1);
	      send (cfdt, &cbuff, sizeof (cbuff), 0);
	    }
	  printf ("\nAll msgs sent to client %s\n", cmname);
	  qwe->snd = qwe->rcv = qwe->msgcnt = 0;
	qwe->lck=0;
	}
      else if (!strcmp (cmd, RCV))
	{
	  que_t *asd;
	  memset(&asd,0,sizeof(asd));
	  recv (cfdt, &cbuff, sizeof (cbuff), 0);
	  asd=search(&start,cbuff.dest);
	
	  if(!asd){
	      send (cfdt,ILGCLI, sizeof (ILGCLI), 0);
	      continue;
		}
	  else if (asd->rcv == 1024  || 
	      asd->rcv + cbuff.attr.sndr_sz + cbuff.attr.sub_sz + cbuff.attr.msg_sz > 1024)
	    {
	      send (cfdt,EBUFF, sizeof (EBUFF), 0);
	      continue;
	    }
	  else
	    {
	      send (cfdt, OK, sizeof (OK), 0);
	    }
	while(asd->lck);
	asd->lck=1;
//printf("%s\n",cbuff.sndr);
//printf("%s\n",cbuff.subjct);
//printf("%s\n",cbuff.msg);
	  strcpy(asd->buff + asd->rcv,cbuff.sndr);
//printf("#%s\n",asd->buff+asd->rcv);
	  asd->rcv += cbuff.attr.sndr_sz;
	  strcpy(asd->buff + asd->rcv,cbuff.subjct);
//printf("#%s\n",asd->buff+asd->rcv);
	  asd->rcv += cbuff.attr.sub_sz;
	  strcpy(asd->buff + asd->rcv,cbuff.msg);
//printf("#%s\n",asd->buff+asd->rcv);
	  asd->rcv += cbuff.attr.msg_sz;
	
	  (asd->msgcnt)++;

	printf ("%s: Mail recieved\n", cbuff.sndr);
	asd->lck=0;
	}
    }
}
