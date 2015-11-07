include ../../Makefile.inc

P=memalloc/part4/

all:	
	${GCC} mallinfo.c -o mallinfo ${ECHO}mallinfo.c
	${GCC} malloc.c -o malloc ${ECHO}malloc.c
	${GCC} malloc_stats.c -o malloc_stats ${ECHO}malloc_stats.c
	${GCC} malloc_usable_size.c -o malloc_usable_size ${ECHO}malloc_usable_size.c
	${GCC} mallopt.c -o mallopt ${ECHO}mallopt.c
	${GCC} test.c -o test ${ECHO}test.c
clean : 
	${RM} *~ mallinfo malloc malloc_usable_size mallopt test	\
	 malloc_stats

