//create and open a new possix msgQ;

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>

main(){

	mqd_t mid;
	if(mid = mq_open("/create",O_RDWR|O_NONBLOCK|O_CREAT/*|O_EXCL*/,0664,NULL)==(mqd_t )-1) perror("mq_open"),exit(1);
		//Name must be start with slash '/'  dont give like: /tmp/notify1 like that
		
	printf("mid = %u\n",mid);

}

/*
NOTES:
        To see the created possix msgQ first u hav to 1st mount the "mqueue" file system..By using 
                                "sudo mount -t mqueue null /mnt"
	{or}
	Create one directory in /dev/mqueue then mount to /dev/mqueue

        so we hav mounted that to /mnt directory..

        now to see the created msgQ "ls /mnt/"..
        To see the entities of a spcefied msgque "cat /mnt/<msgQ_name>"
*/
