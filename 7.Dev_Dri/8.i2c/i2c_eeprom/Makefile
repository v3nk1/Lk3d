#obj-m := atc_eeprom1.o
#obj-m += atc_eeprom2.o
obj-m += atc_eeprom3.o

KDIR :=/embedded/mini2440/uImages/eeprom/linux-3.15.3

PWD := $(shell pwd)

default:
	 $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	 arm-linux-gcc eeprom_test.c -o eeprom_test	 
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean












