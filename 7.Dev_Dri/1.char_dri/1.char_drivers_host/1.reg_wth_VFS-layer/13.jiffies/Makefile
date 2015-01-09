obj-m:= jiffy.o

KDIR=/lib/modules/$(shell uname -r)/build

all:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	@echo "inserting module.."
	@insmod jiffy.ko

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	@echo "removing module.."
	@rmmod jiffy
