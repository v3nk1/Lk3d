
#include"headers.h"

struct seq_lock{
		
	spinlock_t spin;
	int cnt;

	}seqlock_t;

//writer logic

wlock(spinlock_t *){

	pthread_spin_lock(&spinlock_t->spin);

}

wunlock(spinlock_t *p){

	p -> cnt++;//use atomic opereation..
	pthread_spin_unlock(spin);
//one more flag use here
	}
	
//reader logic

	do{
		old = getstatus();
		


		new = getstatus();

	}while(old!=new)
