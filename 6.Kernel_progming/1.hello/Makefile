obj-m:=hello.o

KDIR=/lib/modules/$(shell uname -r)/build 

all: 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
