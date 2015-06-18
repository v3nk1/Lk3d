#ifndef __DLOCK__
#define __DLOCK__

#define data_lock(addr) {				\
	        sem_wait(&addr->sem);			\
		}


#define data_unlock(addr) {				\
		        sem_post(&addr->sem);		\
			sem_close(&addr->sem);		\
			}

#endif
