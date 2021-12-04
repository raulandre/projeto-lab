#include "fila.h"
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

int  retira(fila *q)
{
    struct no *aux;
    if (q->inicio == NULL)
        return 0;

    aux = q->inicio;


    q->inicio = q->inicio->prox;
    free(aux);

    if (q->inicio == NULL)
        q->fim = NULL;
    return 1;
}

void cria(fila *q)
{
	q->inicio = NULL;
	q->fim = NULL;
}

struct no *getq(fila *q, size_t index)
{
	struct no *b = q->inicio;
    	for(int i = 0; i < index; i++)
	{
		if(b == NULL) return NULL;
	        b = b->prox;
	}

	return b;

}
