obj-m :=alloc_page.o
obj-m +=kmalloc.o
obj-m +=structpage.o
obj-m +=kmem_cache2.o
obj-m +=kmem_cache3.o
obj-m +=mycache.o
obj-m +=dma_test3.o
obj-m +=fbmap.o


KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
