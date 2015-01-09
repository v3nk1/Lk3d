#include<pthread.h>
#include<strings.h>

#include<malloc.h>

typedef struct node{
	int data;
	struct node *next;
	}*list_t;

struct passing{
	list_t *lptr;
	int val;
};

pthread_t tid1,tid2;

void list_init(list_t *lptr){

	bzero(lptr,sizeof(*lptr));
	
}

void *insertFunc(void *arg){
	
	list_t *lptr = ((struct passing *)arg)->lptr;
	int val = ((struct passing *)arg)->val;

	list_t new = malloc(sizeof(struct node));
		if(!new){
			printf("melloc: Failed to allocate mem\n");
			return (void *)-1;
			}
			
		new->data = val;
		
	if(!*lptr){
		new->next=NULL;
		*lptr=new;
		return (void *)0;
		}
	
		
		new->next = *lptr;
		*lptr = new;

	return (void *)0;		

}

int insert_first(list_t *lptr,int val){

	struct passing pass;
	pass.lptr=lptr;
	pass.val=val;

	pthread_create(&tid1,NULL,insertFunc,&pass);
	pthread_join(tid1,NULL);

}

void *printFunc(void *arg){

	list_t list = arg;
	
	if(!list){
		printf("List is empty\n");
		return;
		}

	list_t tmp = list;

	while(tmp){

		printf("%d ",tmp->data);
		tmp = tmp->next;
		
	}
	
printf("\n");

}

int print(list_t list){

	pthread_create(&tid2,NULL,printFunc,list);
	pthread_join(tid2,NULL);

}
