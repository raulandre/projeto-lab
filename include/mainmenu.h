#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include <ncurses.h>

void destroy_win(WINDOW *);
WINDOW *crete_newwin(int, int, int, int);
void rowMenu(int, int);
void clientsMenu(int, int);
void mainMenu();
void printMenu();

#endif 
