#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "list.h"
#include "queue.h"

#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

void destroy_win(WINDOW *);
WINDOW *crete_newwin(int, int, int, int);
void rowMenu(list*, fila*, int, int);
void clientsMenu(list*, fila*, int, int);
void mainMenu(list*, fila*, int, int);
void printMenu(list*, fila*);
void rowViewMenu (list*, fila*, int, int, int);
#endif 
