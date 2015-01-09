#Here i used ifeq

val=

HEADER_FILES=../myapp

FILE_EXISTS:=

ifeq ($(wildcard $(HEADER_FILES)),) #(or) ifeq "$(wildcard $(HEADER_FILES)),""
FILE_EXISTS = 0

else
FILE_EXISTS = 1

endif


all:
	#if [ 1 -eq 0 ]; then echo "asdf"; fi;
	if [ $(FILE_EXISTS) -eq 1 ]; then rm ../myapp && echo "file myapp removed"; else touch ../myapp; fi;

crta:
	touch ../myapp
	@echo 'myapp file created'

rm:
	rm ../myapp
	@echo "file myapp has removed"
