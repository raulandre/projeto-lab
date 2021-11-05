
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "mainmenu.h"


void destroy_win(WINDOW *local_win){
      wclear(local_win);
      wborder (local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
      wrefresh(local_win);
      delwin(local_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  wrefresh(local_win);

  return local_win;
}

void rowMenu(int yMax, int xMax){
	WINDOW * rowwin;

	rowwin = create_newwin(8,40, (yMax/2)-4, (xMax/2)-20);
	refresh();
	box(rowwin,0,0);
	wrefresh(rowwin);

	keypad(rowwin, true);
	char rowChoices [4] [40] = {"Mostrar a Fila", "Adicionar","Chamar o Proximo", "Voltar"};
	int rowChoice, highlight = 0, rowOption;


	while(1) {	
		for(int i = 0; i < 4; i++){
			if(i == highlight)
				wattron(rowwin,A_REVERSE);
			mvwprintw(rowwin, i+2, 1,"\t%s", rowChoices[i]);
			wattroff(rowwin,A_REVERSE);
			wrefresh(rowwin);
		}
		rowChoice = wgetch(rowwin);

		switch(rowChoice){
			case KEY_UP:
				highlight--;	
				if(highlight == -1)
					highlight = 2;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 4)
					highlight = 0;
				break;
			case 10:
				rowOption = highlight+1;
				switch(rowOption){
					case 1:
						break;
					case 2:
						break;
					case 3: 
						break;
					case 4:
						mainMenu();
						break;

				}
		}
	}

}

void clientsMenu(int yMax, int xMax){
	WINDOW * clientwin;

	clientwin = create_newwin(8,40, (yMax/2)-4, (xMax/2)-20);
	refresh();
	box(clientwin,0,0);
	wrefresh(clientwin);

	keypad(clientwin, true);
	//esolha
	char clientsChoices [3] [22] = {"Criar um Cliente", "Listar Um Cliente", "Voltar"};
	int clientChoice, highlight = 0, clientOption;

	while(1) {
		for(int i = 0; i < 3; i++){
			if(i == highlight)
				wattron(clientwin,A_REVERSE);
			mvwprintw(clientwin, i+2, 1,"\t%s", clientsChoices[i]);
			wattroff(clientwin,A_REVERSE);
			wrefresh(clientwin);
		}
		clientChoice = wgetch(clientwin);

		switch(clientChoice){
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 2;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)
					highlight = 0;
				break;
			case 10:
				clientOption = highlight+1;
				switch(clientOption){
					case 1:
						break;
					case 2:
						break;
					case 3:
						mainMenu();
						break;
				}
		}
	}


}

void mainMenu(){
	// tamanho da tela
	int yMax, xMax, aux = 0;
	getmaxyx(stdscr, yMax, xMax);

	//criando box
	WINDOW * win;

	//WINDOW * win = newwin(10,50, (yMax/2)-5,(xMax/2)-25);
	win = create_newwin(8, 40, (yMax / 2) - 4,(xMax / 2) - 20);
	refresh();
	box(win,0, 0);
	wrefresh(win);

	//interacao com o teclado
	keypad(win, true);

	//menu
	char choices[3][9] = {"Clientes", "Fila", "Sair"};
	int choice, highlight = 0, option;

	while(!aux) {
		for (int i = 0; i < 3; i++){
			if (i == highlight)
				wattron(win, A_REVERSE);
			mvwprintw(win, i+2, 1,"\t%s", choices[i]);
			wattroff(win,A_REVERSE);
			wrefresh(win);
		}
		choice = wgetch(win);

		switch(choice) {
			case KEY_UP:
				highlight--;
				if (highlight == -1)
					highlight = 2;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3)
					highlight = 0;
				break;
			case 10:
				option = highlight + 1;
				switch(option){
					case 1:
						clientsMenu(yMax, xMax);
						break;
					case 2:
						rowMenu(yMax, xMax);
						break;
					case 3:
					default:
						refresh();
						aux = 1;
						// exit(0);
						break;

				}
				break;
			// default:
				// break;
		}

	}
	endwin();
	// destroy_win(win);
	return;
}

void printMenu(){
	// inicializando ncurses
	initscr();
	noecho();
	cbreak();
	mainMenu();
}
