#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/mm.h>

struct memcg_register_cache_work {
        struct mem_cgroup *memcg;
        struct kmem_cache *cachep;
        struct work_struct work;
};


struct kmem_cache *mycache;
void *object,*object1;
char *ptr;
int kmem_init(void)
{

	pr_info("#%d\n",sizeof(struct memcg_register_cache_work));
       mycache = kmem_cache_create("test_cache",64, 0, SLAB_RED_ZONE, NULL);
       if (!mycache)
	    return -ENOMEM;
	
	pr_info("cache size %d\n", kmem_cache_size(mycache));
	pr_info("act size: %d, padded size: %d\n",mycache->object_size,mycache->size);
	object = kmem_cache_alloc(mycache, GFP_KERNEL);
//	object1 = kmem_cache_alloc(mycache, GFP_KERNEL);
	ptr=object;
	memset(ptr,'A',64);
	if (!object)
		return -ENOMEM;

	return 0;
}

void kmem_exit(void)
{
	int i;
	for(i=0;i<50;i++)
		printk("%c ",ptr[i]);
	pr_info("\n");
	kmem_cache_free(mycache, object);
	kmem_cache_destroy(mycache);
}

EXPORT_SYMBOL(ptr);

module_init(kmem_init);
module_exit(kmem_exit);

MODULE_AUTHOR("support@techveda.org");
MODULE_DESCRIPTION("LKD_CW: cache");
MODULE_LICENSE("GPL");
