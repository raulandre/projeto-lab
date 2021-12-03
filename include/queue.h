#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "client.h"

struct no
{
    client c;
    struct no *prox;
};

typedef struct
{
    struct no *inicio;
    struct no *fim;
} fila;

int  insere(fila *q, client);
int  retira(fila *q);
void cria(fila *q);
struct no *getq(fila *q, size_t index);

#endif // QUEUE_H
