

#ifndef _CIRC_ERR /*Error no's for circular linked list*/

#define _CIRC_ERR

#include <stdio.h>

int errno;

enum {
	EEMPTY=-7,
	EFULL,
	EEND,		/*Reached end*/
	ENOTFND,
	EMALLOC,	/*Malloc fail*/
	EDUPFND,	/*Duplicate found*/
	FAILURE=-1,
	SUCCESS=0
				
	};

#endif
