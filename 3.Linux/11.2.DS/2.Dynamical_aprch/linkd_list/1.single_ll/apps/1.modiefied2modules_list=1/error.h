#include"errno.h"
#ifndef ERRMSG 

#define ERRMSG
void errmsg(char *str){

        switch(errno){

                        case ENODUP:
                                        printf("%s: No dup found\n",str);
                                        break;
                        case EFOUND:
                                        printf("%s: Element not found\n",str);
                                        break;
                        case EEPTY:
                                        printf("%s: Q is empty\n",str);
                                        break;
                        case EFULL:
                                        printf("%s: Q is full\n",str);
                                        break;
                        case EMALL:
                                        printf("%s: Failed in alloc mem\n",str);
                                        break;
                        case FAILURE:
                                        printf("%s: Failed\n",str);
                                        break;
                        case SUCCESS:
                                        printf("%s: Success\n",str);
                                        break;
                        default   :
                                        printf("%s: No errno is set\n",str);
                                        break;
        }

}
#endif
