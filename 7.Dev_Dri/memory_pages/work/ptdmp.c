#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/highmem.h>

static int major;
static void *kptr1, *kptr2;

int ptd_open(struct inode *i, struct file *filp)
{
	return 0;
}

int ptd_close(struct inode *i, struct file *filp)
{
	return 0;
}

static unsigned long getDirEntry(const pgd_t *pgd, void *address)
{
	unsigned long d_index;
	unsigned long *pgd_array = (unsigned long *)pgd;
	unsigned long tmp;

	unsigned long t = (unsigned long)address;
	d_index = t >> 22;
	tmp = pgd_array[d_index];
	tmp = tmp >> 12;
	tmp = tmp << 12;
	return tmp;
}

static unsigned long getPageTableEntry(unsigned long d, void *address)
{
	unsigned long t;
	unsigned long *pte_array = (unsigned long *)d;
	unsigned long tmp;

	t = (unsigned long)address;
	t = t << 10;
	t = t >> 22;

	tmp = pte_array[t];
	tmp = tmp >> 12;
	tmp = tmp << 12;
	return tmp;
}

ssize_t ptd_read(struct file *filp,char __user *buf, size_t count, loff_t *fpos)
{
	unsigned long d, pte, t;
	unsigned int pfn, pfn2;
	struct page *pptr, *pptr2;
	
	struct mm_struct *mm = current->mm;
	pgd_t *pgd = mm->pgd;

	printk("%s: Data red: %s\n",__func__,buf);

	printk("KERNEL:Address (virtual) of buf received = %p\n",buf);
	printk("KERNEL:Address of page global directory = %p\n",pgd);
	d = getDirEntry(pgd,buf);
	/* d get the physical addr of page table of buf from pgd */
	printk("KERNEL: Address of page Table  = %08x\n",
						(unsigned int)d);
pr_info("%s:1\n",__func__);
	pfn = d >> 12; /* page to frame number */
	printk("frame number of page Table = %08x\n",pfn);
pr_info("%s:2\n",__func__);
	pptr = pfn_to_page(pfn);/* getting page addr from pfn */
	pr_info("%s:3\n",__func__);
	printk("Address of struct page of Page Table = %p\n",pptr);
	pr_info("%s:4\n",__func__);
	kptr1 = kmap(pptr);
	pr_info("%s:5\n",__func__);
	pte = getPageTableEntry((unsigned long)kptr1,buf);
	pr_info("%s:6\n",__func__);
	printk("KERNEL:Physical address of frame = %08x\n",
						(unsigned int)pte);
	pfn2 = pte >>12;
	pr_info("%s:7\n",__func__);
	pptr2 = pfn_to_page(pfn2);
	pr_info("%s:8\n",__func__);
	kptr2 = kmap(pptr2);
	pr_info("%s:9\n",__func__);
	printk("KERNEL:Frame mapped to page  = %p\n",kptr2);
	pr_info("%s:a\n",__func__);
	t = (unsigned long)buf;
	pr_info("%s:b\n",__func__);
	t = t << 20;
	pr_info("%s:c\n",__func__);
	t = t >> 20;
	pr_info("%s:d\n",__func__);
	printk("Value of string inside physical page = %s\n",(char *)kptr2+t);
	pr_info("%s:e\n",__func__);
	kunmap(kptr1);
	kunmap(kptr2);


	return 0;
}

struct file_operations ptd_fops = {
	.owner		= THIS_MODULE,
	.open		= ptd_open,
	.release	= ptd_close,
	.read		= ptd_read,
};

int init_module(void)
{
	printk("Loading ptdump\n");
	printk("pgdir_shift: %d\n",PGDIR_SHIFT);
	printk("pgdir_shift: %d\n",PTRS_PER_PGD);
	major = register_chrdev(0,"addtrans",&ptd_fops);
	if ( major <= 0 ) {
	   printk("Error in registering character device\n");
	   return -1;
	}
	else printk("Assigned major number = %d\n",major);
	
	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(major,"addtrans");
	printk("Unloading\n");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("support@techveda.org");

