obj-m:= rtc_procsfs_dri.o


KDIR=/lib/modules/$(shell uname -r)/build



all:	rtc_procsfs_dri.c
		
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules  	
		insmod rtc_procsfs_dri.ko 	

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rmmod rtc_procsfs_dri #to automate the job of removing the module
