

IPC's(semaphore's,mutex's,sharedmemory's,msgqueue's)
====================================================

	- Semaphores are used for data synchronisation between two threads/process
		-- In threads All the global data is Shared by default
		-- In parent child scenarios like fork(), copy-on-write takes place, use a shared memory
		   to make sure that they are sharing a global data.
		-- In two different process also use shared memory inorder to have same global resource
		   b/w the two processes.

	-  Semaphores ->|-> SysV 
			|
		        |-> Posix ->|
		      	            |-> Named semaphores
		      		    |-> Unnamed semaphores

Posix-Named semaphores:
----------------------

- Here we don't use sem_init()
- These created @ /dev/shm
	ls /dev/shm/


Posix-Unnamed semaphores:
------------------------

	Here we use sem_init()
