#include "queue.h"
#include "client.h"

int  insere(fila *q, client d)
{

    struct no *aux;

    aux = (struct no*) malloc(sizeof(struct no));

    if (aux == NULL)
        return 0;

    aux->c = d;

    aux->prox = NULL; 

    if (q->inicio == NULL)
    {
        q->inicio = aux;
        q->fim = aux;
        return 1;
    }

    q->fim->prox = aux;
    q->fim = aux;
    return 1;
}

int  retira(fila *q, client *d)
{
    struct no *aux;
    if (q->inicio == NULL)
        return 0;

    aux = q->inicio;

    *d = q->inicio->c;

    q->inicio = q->inicio->prox;
    free(aux);

    if (q->inicio == NULL)
        q->fim = NULL;
    return 1;
}

void mostra(fila q)
{
    struct no *aux;
    if (q.inicio == NULL)
        printf("\nFila vazia...\n\n");
    else
    {
        aux = q.inicio;
        while (aux != NULL)
        {
            print_client(aux->c);
            aux = aux->prox;
        }
    }
}
