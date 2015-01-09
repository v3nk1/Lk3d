# to use 'global int i' here also i copy the source file(Module.symvers) where 'i' has declared to this directory and then gv make

obj-m:= wr.o

KDIR=/lib/modules/$(shell uname -r)/build

all: copy wr.c
	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

copy:
	if [ -e ../ins_mod/Module.symvers ]; \
	then cp ../ins_mod/Module.symvers ./ ;\
	else cd ../ins_mod/ && make && cp ./Module.symvers ../wr_mod ;\
	fi;

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
