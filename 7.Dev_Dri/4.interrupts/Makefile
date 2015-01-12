#obj-m:= interrupt.o
#obj-m:= workq.o
#obj-m:= workq_new.o
#obj-m+= tasklets.o
#obj-m+= usr2kern_sig.o
obj-m+= threaded_irq.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
#	insmod interrupt.ko irq=$(IRQ)

clean:
	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
#	rmmod interrupt
