#obj-m:= rtc_gen2kernel.o
obj-m:= rtc_seq_file.o
#obj-m:= rtc_oldkernel.o
#obj-m:= rtc1.o
#obj-m:= proc.o

KDIR=/lib/modules/$(shell uname -r)/build

#rtc_seq_file.o:
all:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	#@insmod rtc_seq_file.ko @#to automate the job of inserting module

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	#@rmmod rtc_seq_file @#to automate the job of removing the module
