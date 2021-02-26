#include "data_structs.h"

List createList(){
    return NULL;
}

List appendHead(List l, void *data){
    List f = malloc(sizeof(struct NODE));
    f->data = data;
    f->next = l;
    return f;
}

List popHead(List l, void *data){
    return l->next;
}

int isListEmpty(List l){
    return l == NULL;
}

// BAD IMPLEMENTATION, IF A STRUCT WITH SIZE > 64B IS PASSED IT WILL LIKELY BREAK
// OR HAVE UNDEFINED BEHAVIOUR
int isDataIn(List l, void *data, unsigned int data_size){
    List tmp = l;

    while(!isListEmpty(tmp)){
        if(memcmp(tmp->data, data, data_size) == 0)
            return 1;
        tmp = tmp->next;
    }

    return 0;
}