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
void mostra(fila q);

#endif // QUEUE_H
