#include<stdio.h>

struct msg {
        char str[20];
        int len;
   };

main(){

	struct msg o={"veda solutions",strlen(o.str)};
	struct msg *po=&o;
	struct msg **ppo=&po;

	strcpy(po->str,"sol veda");
	(*ppo)->len=strlen(o.str);
	/* or
	 * (**ppo).len is equal to (*ppo)->len
	 */

	printf("%s ==== %d\n",o.str,o.len); 

}
