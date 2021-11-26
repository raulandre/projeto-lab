#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "list.h"

#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

void destroy_win(WINDOW *);
WINDOW *crete_newwin(int, int, int, int);
void rowMenu(list*, int, int);
void clientsMenu(list*, int, int);
void mainMenu(list*);
void printMenu(list*);

#endif 
