/*
    NOT USED YET 
*/

#pragma once

#include <stdlib.h>

typedef struct NODE{
    void *data;
    struct NODE *next;
}*List;

List createList();
List appendHead(List l, void *data);
List popHead(List l, void *data);

int isListEmpty(List l);
