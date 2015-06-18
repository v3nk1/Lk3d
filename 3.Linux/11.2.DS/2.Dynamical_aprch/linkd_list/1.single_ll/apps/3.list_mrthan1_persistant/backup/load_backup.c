#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#include<errno.h>

#include"../headers/lheaders.h"
#include"../headers/nheaders.h"

//this is a structure defined by me to ease of storing the data in a parsistant file..
struct list_entities{//all this is global data..

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

int load_backup(void){

	int fd=open("./backup/save/list",O_RDWR);
			
	if(fd==-1) {
		  // perror("open");
		   printf("Error: No backup found\n");
		   return -1;
		}		

	struct list_entities val;
	read(fd,&val,sizeof(val));
			//we get populated list_entities struct object(val) by invoking read itself
	cnt=val.lcnt;

	struct back_up __bkup;	
	
	list_t *lprev = NULL;
	int i=0;
	while(i++ < val.lcnt){//dont give <= here, causes one extra loop
		
		if(read(fd,&__bkup,sizeof(__bkup))==-1) perror("read(load_bakup)"),exit(100);//fread 
				//becareful for read function, always better to check the return value(in case of error)// error means what if u close(fd) in this while loop only instead of after post-amble of this while that will cause problem na, actually it doesnt throw any error becoz we didnt check the return value, so it fails normally rest of code will executes.. But here __bkup has previous values only since read doesnt invoked successfully..
		
				
		list_t *lnew = malloc(sizeof(list_t));
		if(!lnew){
			printf("Failed to load backup, TRY AGAIN(restart the app)\n");
			exit(1);
			}

		if(i==1){
			l1st=lnew;//no need to check if(val.l1st_id==__bkup.lid)
			lcurr=lnew; //if only one list is there..
			lnew->lnext = NULL;
			lnew->lno=__bkup.lid;
			strcpy(lnew->lname,__bkup.lname);
			lnew->cnt=__bkup.ncnt;
			lprev = lnew;
			}
		if(i>1){

			if(val.lcurr_id==__bkup.lid) lcurr=lnew;
			lnew->lno=__bkup.lid;
			strcpy(lnew->lname,__bkup.lname);
			lprev->lnext=lnew;
			lnew->lnext=NULL;
			lnew->cnt=__bkup.ncnt;
                        lprev = lnew;
			}

		int j=0;
		que_t *nnew,*nprev;
		//qtmp=ltmp->lstart;
			while(j++ < lnew->cnt){//dont give <= here, causes one extra loop
				read(fd,&bdata,sizeof(bdata));
				nnew = malloc(sizeof(que_t));
				
				if(j==1){
					lnew->lstart=nnew;
					nnew->data = bdata;
					nnew->next = NULL;
					nprev = nnew;
					}
					
				if(j>1){
					nnew->data = bdata;
					nnew->next = NULL;
					nprev->next = nnew;
					nprev = nnew;
					}
		//ltmp=ltmp->lnext;

			}
//becareful dont give close(fd) here..
}

printf("Loading backup has done\n\n");

close(fd);

}
