#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr)-(char *)(&((type *)0)->member)))

struct test1 {
	int a;
};

struct test2 {
	int b;
	struct test1 z;
	char ch;
	short sh;
	struct test1 *pz;
	int c;
};

int main()
{
	/* existing structure */
	struct test2 *obj;
	obj = malloc(sizeof(struct test2));
	if (obj == NULL) {
		printf("Error: Memory not allocated...!\n");
		exit(1);
	}
	obj->z.a = 10;
	obj->b = 20;
	obj->c = 30;
	obj->ch = 40;
	obj->sh = 50;
	obj->pz=&obj->z;

	/* pointer to existing entry */
	struct test1 *obj1 = &obj->z;

	struct test2 *obj2= container_of(&obj->c,struct test2,c);
	printf("%p:%p\n",obj2,obj);
	printf("@%lu:%lu\n",(size_t) &((struct test2 *)NULL)->pz,((size_t) &((struct test2 *)0)->pz));
//	printf("#%lu\n",(size_t) ((struct test2 *)0)->b );


//	printf("obj2->b = %d\n", obj2->b);

	return EXIT_SUCCESS;
}
