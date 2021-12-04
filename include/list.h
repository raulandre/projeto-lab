#ifndef LIST_H
#define LIST_H

#ifndef __GNUC__
#error Temos 'delete' como identificador de funcao, por favor use um compilador C :P 
#endif

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
int push_back(list*, client); //Adiciona no final
int push_front(list*, client); //Adiciona no inicio
int insert(list*, unsigned int, client); //Insere em qualquer indice
void shift(list*); //Remove o primeiro
void pop(list*); //Remove o ultimo
void delete(list*, unsigned int); //Remove de qualquer indice
struct node* get(list, unsigned int); //Retorna o no em um determinado indice
#endif // LIST_H
