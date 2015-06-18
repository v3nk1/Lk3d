SGCC=gcc
SRM=rm
all:	
	${SGCC} main.c -lrt -lpthread -o main  
	${SGCC} reader.c -lrt -lpthread -o reader 
	${SGCC} writer.c -lrt -lpthread -o writer  
clean : 
	${SRM} main reader writer

