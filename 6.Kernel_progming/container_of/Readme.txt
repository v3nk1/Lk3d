Container_of():
---------------
Macro:
-----
This always returns start address/base address of the structure.
This always used with structure type only.
/*
 * @ptr: address of the structure member.
 * @type: In which it is belonging to.
 * @member: Name of the member(variable name).
 */

/** 
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
	#define container_of(ptr, type, member) ({                      \
        	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        	(type *)( (char *)__mptr - offsetof(type,member) );})

	#define container_of(ptr, type, member) 							\
					((type *)((char *)(ptr)-(char *)(&((type *)0)->member)))

	See the beauty of this macro replacement, 
		-- What ever the pointer address you've passed is type-casted to (char *) then
		   subtracted with what "&((type *)0)->member"
		-- Take a NULL pointer or 0 and type-cast it to the pointer type you've passed
		   then de-refer the member u passed then it will give the sizeof container up to the
		   particular member.

		   If u remove '&' there will cause segmentation fault, bcoz of dereference NULL.

		-- Means since we are using 0 address here, and type-casted to struct ptr type and
		   Accessing a member means it will increment sizes upto that member.
		   For example:
		   ------------
			(&((type *)0)->member)  replaced with (&((struct alphbt *)0)->e)	

			say i know e address.
				address = 0 = First offset
				address = 0 + sizeof(1st member(a)) = 4 = 2nd offset
				address = 4 + sizeof(2nd member(b)) = 8 = 3rd offset
				address = 8 + sizeof(3rd member(c)) = 12= 4th offset
				address = 12+ sizeof(4th member(d)) = 14= 5th offset
				address = 14;
			Subtract with 14 will result base address.

		-- So subtract it will result base address. 
	
	Let us assume a structure which contains alphabets a to z as members.

	struct alphbt {
	
		int a;
		int b;
		int c;
		short d;
		long e;
		char f;
		long long g;
		int h;
		int i;
		int j;
		int k;
		int l;
		int m;
		int n;
		int o;
		int p;
		int q;
		int r;
		int s;
		int t;
		int u;
		int v;
		int w;
		int x;
		int y;
		int z;

	};

	
	- I've an address of member g; And i want to accesss member c. I know the
	  Structure tag name, i know the type of the varible name.

	- Then you can use container_of(ptr,type,name);
	  This always returns start address/base address of the structure.

	- Snippet:
	  -------
		struct tag *g_ptr=&obj->g;
		struct tag *base=container_of(g_ptr,struct tag,g);
		
		/* Accessing member c */
		base->c=1234;
