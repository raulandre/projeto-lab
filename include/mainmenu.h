#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "list.h"
#include "fila.h"

#include <ncurses.h>

void destroy_win(WINDOW *);
WINDOW *crete_newwin(int, int, int, int);
void rowMenu(list*, fila*, int, int);
void clientsMenu(list*, fila*, int, int); // Menu de clientes
void mainMenu(list*, fila*, int, int); //Boilerplate do ncurses
void printMenu(list*, fila*); //Menu principal
void rowViewMenu (list*, fila*, int, int, int); //Exibicao da fila
#endif 
