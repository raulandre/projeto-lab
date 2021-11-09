#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

void destroy_win(WINDOW *);
WINDOW *crete_newwin(int, int, int, int);
void rowMenu(int, int);
void clientsMenu(int, int);
void mainMenu();
void printMenu();

#endif 
