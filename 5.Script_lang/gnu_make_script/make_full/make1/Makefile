#This makefile to check whether the its parent directory consisting a file specifed in SEARCH

val:=  #this is just declared variable but no value in it..

SEARCH_PATH=..#search path
SEARCH:=myapp#search file

FILE_EXISTS:=	#to store the file status

#IT IS GNU MAKE SCRIPT SYNTAX:
ifneq ($(wildcard $(SEARCH_PATH)/$(SEARCH)),) #(OR)	ifneq "$(wildcard $(SEARCH)),""
	#wildcard: here we are comparing it with empty string thats why 2nd argument is empty just a comma has putted, We are comparing with empty string bcoz if the file given in the 1st argument not found then it will return an empty sring.. We can use ifeq condition also..
FILE_EXISTS = 1
else
FILE_EXISTS = 0
endif


all:
	#if [ 1 -eq 0 ]; then echo "asdf"; fi;
	#IT IS BASH SCRIPT SYNTAX(since these commands will execute in bash only na..)
	#try to write if condition only in one line since continution(\) is not suuported
	if [ $(FILE_EXISTS) -eq 1 ]; then rm $(SEARCH_PATH)/$(SEARCH) && echo "file myapp removed"; else touch $(SEARCH_PATH)/$(SEARCH); fi;

crt:
	touch $(SEARCH_PATH)/$(SEARCH)
	@echo 'myapp file created'

rm:
	rm $(SEARCH_PATH)/$(SEARCH)
	@echo "file myapp has removed"
