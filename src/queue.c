#include "queue.h"

void initq(queue *q)
{
    q->begin = NULL;
    q->end = NULL;
    q->size = 0;
}

int addq(queue *q, client c)
{
    struct nodeq *aux = (struct nodeq*)malloc(sizeof(struct nodeq));
    if(aux == NULL) return 0;

    aux->c = c;
    aux->next = NULL;

    if(q->begin == NULL)
    {
        q->begin = aux;
        q->end = aux;
        q->size++;
        return 1;
    }

    q->end->next = aux;
    q->end = aux;
    q->size++;
    return 1;
}

int shiftq(queue *q)
{
    if(q->size == 0) return 0;

    struct nodeq *aux = q->begin;
    q->begin = q->begin->next;
    free(aux);
    q->size--;

    if(q->begin == NULL) q->end = NULL;

    return 1;
}

int isEmptyq(queue q)
{
    return q.size == 0;
}

struct nodeq* getq(queue q, size_t index)
{
    if(index < 0 || index >= q.size) return NULL;

    struct nodeq *aux = q.begin;
    for(int i = 0; i < index; i++)
    {
        aux = aux->next;
    }

    return aux;
};
