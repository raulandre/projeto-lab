#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "client.h"

struct nodeq
{
    client c;
    struct nodeq *next;
};

typedef struct
{
    struct nodeq *begin;
    struct nodeq *end;
    size_t size;
} queue;

void initq(queue*);
int addq(queue*, client);
int shiftq(queue*);
int isEmptyq(queue);
struct nodeq* getq(queue, size_t);

#endif // QUEUE_H
