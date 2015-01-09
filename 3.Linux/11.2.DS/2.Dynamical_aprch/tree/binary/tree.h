#include<stdio.h>

#ifndef _TREE_H

#define _TREE_H

typedef struct node{

	struct node *lptr;
	char data;
	struct node *rptr;

	}node_t;

node_t T;

#endif
