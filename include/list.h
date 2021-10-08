#ifndef LIST_H
#define LIST_H

#ifndef __GNUC__
#error This code requires specifically a C compiler.
#endif // __GNUG__

#include <stdio.h>
#include <stdlib.h>

#include "client.h"

struct node
{
    struct node *prev;
    client c;
    struct node *next;
};

typedef struct
{
    unsigned int size;
    struct node *begin;
    struct node *end;
} list;

void init(list*);
int push_back(list*, client);
int push_front(list*, client);
int insert(list*, unsigned int, client);
void shift(list*);
void pop(list*);
void delete(list*, unsigned int);
struct node* get(list, unsigned int);
#endif // LIST_H
