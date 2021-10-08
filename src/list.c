#include "list.h"
#include "client.h"

void init(list *l)
{
    l->size = 0;
    l->begin = NULL;
    l->end = NULL;
}

int push_back(list *l, client c)
{
    struct node *aux = (struct node*)malloc(sizeof(struct node));
    if(aux == NULL) return 0;

    aux->c = c;
    if(l->size == 0)
    {
        aux->next = aux;
        aux->prev = aux;
        l->begin = aux;
        l->end = aux;
    }
    else
    {
        aux->next = l->begin;
        aux->prev = l->end;
        l->end->next = aux;
        l->end = aux;
    }

    l->size++;

    return 1;
}

int push_front(list *l, client c)
{
    struct node *aux = (struct node*)malloc(sizeof(struct node));
    if(aux == NULL) return 0;

    aux->c = c;
    if(l->size == 0)
    {
        aux->next = aux;
        aux->prev = aux;
        l->begin = aux;
        l->end = aux;
    }
    else
    {
        aux->next = l->begin;
        aux->prev = l->end;
        l->begin = aux;
        l->end->next = aux;
    }

    l->size++;

    return 1;
}

int insert(list *l, unsigned int index, client c)
{
    if(index < 0 || index > l->size) return 0;

    if(index == 0) push_front(l, c);
    else if(index == l->size) return push_back(l, c);
    else
    {
        struct node *aux = (struct node*)malloc(sizeof(struct node));
        if(aux == NULL) return 0;
        aux->c = c;

        struct node *n = get(*l, index - 1);
        if(n == NULL) return 0;

        aux->next = n->next;
        aux->prev = n;
        n->next = aux;
        n->next->prev = aux;
    }

    l->size++;
    return 1;
}

void shift(list *l)
{
    if(l->size == 0) return;

    struct node *aux = l->begin;

    if(l->size - 1 == 0)
    {
        free(l->begin);
        init(l);
    }
    else
    {
        aux->next->prev = l->end;
        l->begin=aux->next;
        l->end->next = l->begin;
        free(aux);
    }

    l->size--;
}

void pop(list *l)
{
    if(l->size == 0) return;

    struct node *aux = l->end;

    if(l->size - 1 == 0)
    {
        free(l->begin);
        init(l);
    }
    else
    {
        aux->prev->next = l->begin;
        l->end = aux->prev;
        l->begin->prev = aux->prev;
        free(aux);
        l->size--;
    }
}

void delete(list *l, unsigned int index)
{
    if(l->size == 0 || index < 0 || index >= l->size) return;

    if(index == 0) { shift(l); return; }
    else if(index == l->size - 1) { pop(l); return; }
    else
    {
        struct node *aux = get(*l, index);
        if(aux == NULL) return;

        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
        free(aux);
        l->size--;
    }
}

struct node* get(list l, unsigned int index)
{
    if(index < 0 || index >= l.size) return NULL;

    struct node *b = l.begin;
    for(int i = 0; i < index; i++)
        b = b->next;

    return b;
}
