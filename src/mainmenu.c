#include <ncurses.h>
#include <stdio.h>
#include "mainmenu.h"


void destroy_win(WINDOW *local_win){	
      wclear(local_win);
    /* Os parâmetros usados são
    * 1. win: a janela na qual operar
    * 2. ls: caractere a ser usado para o lado esquerdo da janela
    * 3. rs: caractere a ser usado para o lado direito da janela
    * 4. ts: caractere a ser usado na parte superior da janela
    * 5. bs: caractere a ser usado na parte inferior da janela
    * 6. tl: caractere a ser usado para o canto superior esquerdo da janela
    * 7. tr: caractere a ser usado no canto superior direito da janela
    * 8. bl: caractere a ser usado no canto inferior esquerdo da janela
    * 9. br: caractere a ser usado no canto inferior direito da janela
    */ 
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

void printMenu(){
	// inicializando ncurses
	initscr();
	noecho();
	cbreak();

	// tamanho da tela
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//criando box
	WINDOW * win;
	
	//WINDOW * win = newwin(10,50, (yMax/2)-5,(xMax/2)-25);
	win = create_newwin(8,40, (yMax/2)-4,(xMax/2)-20);
	refresh();
	box(win,0,0);
	wrefresh(win);

	//intecao com o teclado
	keypad(win, true);

	//menu
	char choices[3] [9] ={"Clientes", "Fila","Sair"};
	int choice, highlight = 0;

	while(1) {	
		for(int i = 0; i < 3; i++){
			if(i == highlight)
				wattron(win,A_REVERSE);
			mvwprintw(win, i+2, 1,"\t%s", choices[i]);
			wattroff(win,A_REVERSE);
			wrefresh(win);
		}
		choice = wgetch(win);

		switch(choice){
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
			default:
				break;
		}
		if(choice ==10) {
			destroy_win(win);
			win = create_newwin(12, 10, (yMax/2)-5,(xMax/2)-5);
			break;
		}
	}


	//programa me espere, por favor
	getch();
	endwin();


}
