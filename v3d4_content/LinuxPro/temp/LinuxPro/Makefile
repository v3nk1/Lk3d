include ./Makefile.inc

DIRS=attrib Designs fork ioperm lib memalloc net proclimit signals syscall timers \
clone exec io ipc libs multiio posix sched startup threads

all:    
	@ for dir in ${DIRS}; do (cd $${dir};${CPATH};${MAKE} ${MAKEFLAGS}) ; done

clean:
	@ echo "\n\033[3;31m${bold}Cleaned\033[0m..\n"
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} ${MAKEFLAGS} clean) ; done

help:
	@ echo "\033[3;33m\033[4m${bold}\nHelp\033[0m:"
	@ echo "\t'make clean' - For cleaning"
	@ echo "\t'make'       - For building\n"
