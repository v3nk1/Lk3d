/*
 * Sample program for implementing your own aligned memory
 * routines for linux using standard API's not using library
 * routines like posix_memalign(),memalign() & aligned_alloc().
 */

#include <stdio.h>
#include <stdlib.h>

/*We can check alignment by this macro*/
#define is_align(ptr,align)  (unsigned long long)(ptr) & (align -1)

static inline void *
os_aalloc (int size, int align)
{
        void            **p, **q;
        unsigned long   base;
        int             asz;

        asz = size + sizeof *p + align - 1;
        p = malloc (asz);
        if (p == NULL)
                return NULL;
        base = (unsigned long) p + sizeof *p + align -1;
        q = (void **) (base - (base % align));
        q[-1] = (void *) p;
        return (void *) q;
}

static inline void
os_free (void *p)
{
        free (((void **) p)[-1]);
}

int main(void){

	void *ptr = NULL;
	ptr = os_aalloc(2000,64);
	printf("Allocated %s memory.\n",is_align(ptr,64) ? "Not aligned":"Aligned");
	os_free(ptr);
	return 0;

}
