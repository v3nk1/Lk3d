
#include<stdio.h>

#include"../headers/nheaders.h"
#include"../headers/errno.h"
#include"../headers/lheaders.h"

/******************************************************  SORTING A LIST  *******************************************************/

#define start (*_list)->lstart


int sort_list_asc(list_t **_list){//ascending order

        if(!start){//if list is empty
                errno = EEPTY;
                return FAILURE;
                }

        que_t *tmp = start;
        while(tmp->next){//if list has >1 elements  (it fails if list has only one element since "tmp->next = NULL")

                que_t *_tmp = start;

                while(_tmp->next){
                        if(_tmp->data > _tmp->next->data){
                                        int swap = _tmp -> data;
                                        _tmp -> data = _tmp->next->data;
                                        _tmp->next->data = swap;
                                }
                        _tmp = _tmp -> next;
                        }
                tmp = tmp -> next;
        }

        /*if list has only one element no need to sort*/
        return (errno = SUCCESS);

}


int sort_list_desc(list_t **_list){//descending order

        if(!start){//if list is empty
                errno = EEPTY;
                return FAILURE;
                }

        que_t *tmp = start;
        while(tmp->next){//if list has >1 elements  (it fails if list has only one element since "tmp->next = NULL")

                que_t *_tmp = start;

                while(_tmp->next){
                        if(_tmp->data <  _tmp->next->data){
                                        int swap = _tmp -> data;
                                        _tmp -> data = _tmp->next->data;
                                        _tmp->next->data = swap;
                                }
                        _tmp = _tmp -> next;
                        }
                tmp = tmp -> next;
        }

        /*if list has only one element no need to sort*/
        return (errno = SUCCESS);

}



