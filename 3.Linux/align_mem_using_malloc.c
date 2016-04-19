/*
 * Sample program for implementing your own aligned memory
 * routines for linux using standard API's not using library
 * routines like posix_memalign(),memalign() & aligned_alloc().
 *
 * Aligned Memory: The base address of chunk or memory bank should be
 * divisible by 2^n. There is no such alignment like 10 byte alignment.
 * So alignment always be 2^n.
 * And you shuld not check alignement like (ptr % align) ? "aligned" : "not aligned";
 * as this check will pass if even chunk didn't aligned to 2^n like 10 byte alignment.
 */

#include <stdio.h>
#include <stdlib.h>

/*We can check alignment by this macro*/
#define is_align(ptr,align)  !((unsigned long long)(ptr) & (align -1))

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
	int align = 64; /*Always give like 2^n*/
	ptr = os_aalloc(2000,align);
	printf("Allocated %s memory.\n",is_align(ptr,align) ? "Aligned" : "Not Aligned");
	os_free(ptr);
	return 0;

}
