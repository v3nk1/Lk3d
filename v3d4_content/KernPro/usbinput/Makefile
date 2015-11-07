obj-m :=usbkbd2.o

#KDIR=/embedded/mini2440/uImages/eeprom/linux-3.15.3
KDIR=/lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
