#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>

#include<errno.h>

#include"../headers/lheaders.h"
#include"../headers/nheaders.h"

//See here we noneed to back up the addresses, since there are no more once the prog(process) terminated.. So my defined structures doesnt contain any of adress storing contents. As per the requirement i designed structure members..

//this is a structure defined by me to ease of storing the data in a parsistant file.. 
struct list_entities{

	int l1st_id; //to hold reference of 1st list among the bunch of lists..
	int lcurr_id;//to hold the ref of current list..
	char l1st_name[19];
	char lcurr_name[19];
	int lcnt;     //to maintain how many list are present, and give numbering to the lists.. this static makes here security..
	};

struct back_up{//this is a structure defined by me to ease of storing the data in a parsistant file.. The ease of storing is done by create an instance of back_up struct and populate them with relavent data,then by invoking one write call we can write that to entire data to disk(by passing &struct back_up object)..
	
	int lid;
	char lname[19];
	int ncnt;
//	int next_lid; //next list of the current list

	};

int bdata; //backup data

void save_backup(void){

	//int fd = open("/home/ven/venky/3.Linux/11.2.DS/2.Dynamical_aprch/linkd_list/1.single_ll/1.queue/3.list_mrthan1_persistant/backup/save/list",O_CREAT|O_EXCL|O_RDWR,0664);
	int fd = open("./backup/save/list",O_CREAT|O_RDWR|O_TRUNC,0664);
	if(fd==-1){
		perror("open");
		printf("ERROR IN SAVING BACKUP SORRY :(\n\n");
		return;
		}

	struct list_entities val;

	val.l1st_id=l1st->lno;
	val.lcurr_id=lcurr->lno;
	strcpy(val.l1st_name,l1st->lname);
	strcpy(val.lcurr_name,lcurr->lname);
	val.lcnt=cnt;	

	write(fd,&val,sizeof(val));
	syncfs(fd);

	list_t *ltmp=l1st;
	que_t *qtmp;

	struct back_up __bkup;	

	while(ltmp){
		__bkup.lid=ltmp->lno;
		strcpy(__bkup.lname,ltmp->lname);
		__bkup.ncnt=ltmp->cnt;
		//__bkup.next_lid=ltmp->lnext->lno;

		write(fd,&__bkup,sizeof(__bkup));//fwrite
		syncfs(fd);
		
		qtmp=ltmp->lstart;
			while(qtmp && qtmp->data){
				
					write(fd,&(qtmp->data),sizeof(qtmp->data));
					syncfs(fd);
					qtmp=qtmp->next;			
		
					}	

		ltmp=ltmp->lnext;

		}
		
		
	close(fd);
	printf("Backup has saved successfully\n\n");

}
