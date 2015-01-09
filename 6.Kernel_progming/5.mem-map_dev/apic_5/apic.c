#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include <asm/io.h>

#include"apic.h"

void *io; //dont give int * (or) unsigned int * here, since bottom we are adding 0x00 and 0x10 if u want to access correct regesters it must be void pointer(since void ptr increments by 1 byte only)
unsigned int *regsel;
unsigned int *regwin;

void read_apic(void){

	int i,j;//DECLARATIONS MUST BE 1ST
	unsigned int tmp,tmp1,tmp2;
	
	int arr[]={
			0x10,0x12,0x14,0x16,0x18,0x1A,0x1C,0x1E,
			0x20,0x22,0x24,0x26,0x28,0x2A,0x2C,0x2E,
			0x30,0x32,0x34,0x36,0x38,0x3A,0x3C,0x3E,
			0x11,0x13,0x15,0x17,0x19,0x1B,0x1D,0x1F,
			0x21,0x23,0x25,0x27,0x29,0x2B,0x2D,0x2F,
			0x31,0x33,0x35,0x37,0x39,0x3B,0x3D,0x3F
		};

	io = ioremap(IOAPIC_BASE,1024);/*This 1024 is difference of mapping addrs of IOAPIC in /proc */
	regsel = POP_REGSEL(io);//function like macros
	regwin = POP_REGWIN(io);
	
	//create_proc_read_entry(const char *name,umode_t mode, struct proc_dir_entry *base,read_proc_t *read_proc, void * data);
			//its deprecated
	//proc_create_data(const char *name,umode_t mode, struct proc_dir_entry *parent,const struct file_operations *proc_fops, void *data);
	
	iowrite32(0x00,regsel);
//	*regsel = 0x01; dont derefer like this instead use above function for write, those functions are ment for that purpose only.. those are defined in "vi /lib/modules/3.8.0-30-generic/build/include/asm-generic/io.h"

	tmp = ioread32(regwin);
	pr_info("Id reg: %08x\n",tmp);
	pr_info("ID: %x\n",tmp  >> 24 & 0xf);

	iowrite32(0x01,regsel);
	tmp = ioread32(regwin);
	pr_info("version reg: %08x\n",tmp);
	pr_info("Maxredentry: %x\n",tmp>>16 & 0xff);
	pr_info("version: %x\n",tmp & 0xff);

	iowrite32(0x02,regsel);
	tmp = ioread32(regwin);
	pr_info("arbit reg: %08x\n",tmp);
	pr_info("ARBT ID: %x\n",tmp >> 24 & 0xf);
	

for(i=0,j=24;i<24 && j<48;i++,j++){

	iowrite32(arr[i],regsel);
	tmp1 = ioread32(regwin);
	iowrite32(arr[j],regsel);
	tmp2 = ioread32(regwin);

	pr_info("irq%02d: %08x - %08x\n",i+1,tmp1,tmp2 );

	}

}


int __init init_module(void){

	pr_info("APIC module inserted\n");
	return 0;

}

void __exit cleanup_module(void){

	read_apic();
	iounmap(io);
	pr_info("APIC module removed\n");

}

MODULE_LICENSE("GPL");
