#include"errno.h"
#ifndef ERRMSG 

#define ERRMSG
void errmsg(char *str){

        switch(errno){
                        
			case E1LIST:
                                        printf("%s: Only 1 list present\n",str);
                                        break;
                        case ENFND:
                                        printf("%s: No such list\n",str);
                                        break;
                        case ENOLIST:
                                        printf("%s: No lists are found\n",str);
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
