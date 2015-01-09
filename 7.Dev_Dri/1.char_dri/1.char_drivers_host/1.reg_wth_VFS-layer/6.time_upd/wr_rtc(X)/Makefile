#if u give $(PWD) in a Makefile then it means the current path where Makefile existed
obj-m := rdcal.o

CURR_PATH:=$(PWD)
SEARCH_PATH=../calndr_mod
SEARCH_NAME=Module.symvers
val:=

KDIR=/lib/modules/$(shell uname -r)/build 

all: sub_make rdcal.c 
	#echo $(CURR_PATH)"######################################################"
	$(MAKE) -C $(KDIR) SUBDIRS=$(CURR_PATH) modules

sub_make: 
	if [ -e $(SEARCH_PATH)/$(SEARCH_NAME) ]; \
	then cp $(SEARCH_PATH)/$(SEARCH_NAME) ./ ; \
	else cd $(SEARCH_PATH)/ && make && cp ./$(SEARCH_NAME) $(CURR_PATH); \
	fi;

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(CURR_PATH) clean
