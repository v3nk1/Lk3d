#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gfp.h>

extern char *ptr;
int kmem_init(void)
{

	memset(ptr,'B',128);

	return 0;
}

void kmem_exit(void)
{
	int i;
	for(i=0;i<50;i++)
		pr_info("%c ",ptr[i]);
	pr_info("\n");
}
module_init(kmem_init);
module_exit(kmem_exit);

MODULE_AUTHOR("support@techveda.org");
MODULE_DESCRIPTION("LKD_CW: cache");
MODULE_LICENSE("GPL");
