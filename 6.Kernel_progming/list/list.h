#include <linux/slab.h>

typedef struct {
	int data;
	struct list_head list;
	}list_t;

void init_list(list_t *lp){

	memset(lp,0,sizeof(list_t));
	INIT_LIST_HEAD(&lp->list);
}

int insert(list_t *lp,int data){
	
	list_t *new;
	new=kmalloc(sizeof(list_t),GFP_KERNEL);
	if(!new){
		printk("%s: Failed\n",__func__);
		return -1;
		}
	new->data=data;
	list_add_tail(&new->list,&lp->list);
	return 0;	
}

void print(list_t *lp){

	list_t *tmp=NULL;
	list_for_each_entry(tmp,&lp->list,list){
		if(tmp)
			printk("%d ",tmp->data);
	}

/*	
	struct list_head *tmp;
	list_t *cur;
	list_for_each(tmp,&lp->list){
		cur=list_entry(tmp,list_t,list);
		printk("%d ",cur->data);
		}
*/
	printk("\n");
}
