include ../../../../Makefile.inc

P=ipc/shm/part2/

DIRS= shmsync syncre syncunre

all:	
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done
clean : 
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done

