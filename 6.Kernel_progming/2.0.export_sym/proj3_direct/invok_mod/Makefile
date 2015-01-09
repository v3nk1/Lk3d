obj-m := invok.o

KDIR:=/lib/modules/$(shell uname -r)/build

all:	sub_make invok.c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

sub_make:
	if [ -e ../ins_mod/Module.symvers ]; 				 \
	then cp ../ins_mod/Module.symvers ./ ; 				 \
	else cd ../ins_mod && make && cp ./Module.symvers ../invok_mod ; \
	fi;

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
