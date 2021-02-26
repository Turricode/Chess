#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    void *data;
    struct NODE *next;
}*List;

List createList();
List appendHead(List l, void *data);
List popHead(List l, void *data);

int isListEmpty(List l);
int isDataIn(List l, void *data, unsigned int data_size);