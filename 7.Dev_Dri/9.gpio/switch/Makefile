obj-m := switch1.o
obj-m += switch2.o
obj-m += switch3.o

KDIR=/embedded/mini2440/uImages/eeprom/linux-3.15.3
PWD := $(shell pwd)

default:
	 $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	arm-linux-gcc uio_test.c -o uio_test -lpthread
	arm-linux-gcc uio_test1.c -o uio_test1 -lpthread
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean












