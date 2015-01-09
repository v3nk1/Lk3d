#using bash script language only we are finding the given file existed in the given path or not..
exist:=

SEARCH_PATH=..
SEARCH=file

all:
	if [ -e $(SEARCH_PATH)/$(SEARCH) ]; 	\
		then exist=1 echo "milgayi"; 	\
	else exist=0 echo "doesnt found"; 	\
	fi;
	#or if [ -a $(SEARCH_PATH)/$(SEARCH) ]; then echo "milgayi"; else echo "doesnt found"; fi;

