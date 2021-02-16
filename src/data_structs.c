#include "data_structs.h"

List createList(){
    return NULL;
}

List appendList(List l, void *data){
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