#ifndef _ERRMSG
#define _ERRMSG

#include "./errno.h"

void errmsg(char *str){

        switch(errno){

                case SUCCESS:
                                printf("%s: Success\n",str);
                                break;
                case EEMPTY:
                                printf("%s: List is empty\n",str);
                                break;
                case EFULL:
                                printf("%s: List is full\n",str);
                                break;
                case EEND:
                                printf("%s: List reached the end\n",str);
                                break;
                case ENOTFND:
                                printf("%s: Not found\n",str);
                                break;
                case EMALLOC:
                                printf("%s: Mem allocation failed\n",str);
                                break;
                case EDUPFND:
                                printf("%s: Duplicate found\n",str);
                                break;
                }

}
#endif

