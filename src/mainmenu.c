#include <stdio.h>
#include <stdlib.h>
#include "mainmenu.h"
#include "client.h"
#include "serial.h"

#define filename "clients.dat"

client c;
int gSkip = 0;

void destroy_win(WINDOW *local_win)
{
	wclear(local_win);
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);

	return local_win;
}

void rowViewMenu(list *l, fila *f, int yMax, int xMax, int skip)
{
	WINDOW *viewclientwin;

	getmaxyx(stdscr, yMax, xMax);
	viewclientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(viewclientwin, 0, 0);
	wrefresh(viewclientwin);

	keypad(viewclientwin, true);
	wattroff(viewclientwin, A_REVERSE);
	wrefresh(viewclientwin);
	refresh();
        int starty = 1;
        int startx = 1;

    struct no *n = f->inicio;
	if (n != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			struct no *n = getq(f, i + skip);
			if (n != NULL)
			{
				client cl = n->c;
				wattroff(viewclientwin, A_REVERSE);
				wmove(viewclientwin, starty + (i + 1), startx);
				wprintw(viewclientwin, "%s\t%s\t%3.2f", cl.name,
					cl.cpf, cl.balance);
				wattroff(viewclientwin, A_REVERSE);
				wrefresh(viewclientwin);
				n = n->prox;
			}
		}
	}

	int r, quit = 0;
	while(!quit)
	{
		r = wgetch(viewclientwin);
		switch(r)
		{
			case KEY_UP:
				gSkip = gSkip > 0 ? gSkip - 5 : 0;
				rowViewMenu(l, f, yMax, xMax, gSkip);
				break;
			case KEY_DOWN:
				gSkip = gSkip + 5;
				rowViewMenu(l, f, yMax, xMax, gSkip);
				break;
			case 10:			
				quit = 1;		
				destroy_win(viewclientwin);
				rowMenu(l, f, yMax, xMax);
				break;
		}
	}
	gSkip = 0;

	destroy_win(viewclientwin);
	rowMenu(l, f, yMax, xMax);
}

void creteRowMenu(list *l, fila *f, int yMax, int xMax)
{

	WINDOW *createrowwin;

	createrowwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(createrowwin, 0, 0);
	wrefresh(createrowwin);

	keypad(createrowwin, true);
	int id = 0;
	mvwprintw(createrowwin, 1, 1, "Para adicionar um cliente a fila digite o seu Codigo");
	wattroff(createrowwin, A_REVERSE);
	wrefresh(createrowwin);
	refresh();

	echo();
	mvwscanw(createrowwin, 3, 1, "%d", &id);
	for (int i = 0; i < l->size; i++)
	{
		struct node *n = get(*l, i);
		if (n != NULL)
		{
			client cl = n->c;
			if (cl.id == id)
			{
				insere(f, cl);
				mvwprintw(createrowwin, 4, 1, "%d\t%s\t%s\t%3.2f", id, cl.name,
						  cl.cpf, cl.balance);
			}
                }
		n = n->next;
	}

	mvwprintw(createrowwin, 4, 1, "Cliente nao encontrado");

	getch();
	destroy_win(createrowwin);
	rowMenu(l, f, yMax, xMax);
}

void nextRowMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *nextrowwin;

	getmaxyx(stdscr, yMax, xMax);
	nextrowwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(nextrowwin, 0, 0);
	wrefresh(nextrowwin);

	keypad(nextrowwin, true);
	mvwprintw(nextrowwin, 1, 1, "Chamar proximo Cliente da Fila");
	wattroff(nextrowwin, A_REVERSE);
	wrefresh(nextrowwin);
	refresh();
        if(f->inicio !=NULL){
                client cl = f->inicio->c;
                mvwprintw(nextrowwin,2, 1,"%s", cl.name);
        }
        else{
                wprintw(nextrowwin, "Fila Vazia");
        }

        wrefresh(nextrowwin);
        retira(f);
	getch();
	destroy_win(nextrowwin);
	rowMenu(l, f, yMax, xMax);
}

void rowMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *rowwin;

	rowwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(rowwin, 0, 0);
	wrefresh(rowwin);

	keypad(rowwin, true);
	char rowChoices[4][40] = {"Chamar o Proximo", "Adicionar Cliente na Fila", "Mostrar a Fila", "Voltar"};
	int rowChoice, highlight = 0, rowOption, aux = 0;

	while (!aux)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == highlight)
				wattron(rowwin, A_REVERSE);
			mvwprintw(rowwin, i + 2, 1, "\t%s", rowChoices[i]);
			wattroff(rowwin, A_REVERSE);
			wrefresh(rowwin);
		}
		rowChoice = wgetch(rowwin);

		switch (rowChoice)
		{
		case KEY_UP:
			highlight--;
			if (highlight == -1)
				highlight = 3;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 4)
				highlight = 0;
			break;
		case 10:
			rowOption = highlight + 1;
			switch (rowOption)
			{
			case 1:
				refresh();
				destroy_win(rowwin);
				nextRowMenu(l, f, yMax, xMax);

				break;
			case 2:
				refresh();
				destroy_win(rowwin);
				creteRowMenu(l, f, yMax, xMax);
				break;
			case 3:
				refresh();
				destroy_win(rowwin);
				rowViewMenu(l, f, yMax, xMax, 0);
				break;
			case 4:
				refresh();
				destroy_win(rowwin);
				aux = 1;
				mainMenu(l, f, yMax, xMax);
				break;
			default:
				refresh();
				destroy_win(rowwin);
				aux = 1;
				mainMenu(l, f, yMax, xMax);
			}
		default:
			break;
		}
	}
}

void createClientsMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *createclientwin;

	createclientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(createclientwin, 0, 0);
	wrefresh(createclientwin);

	keypad(createclientwin, true);
	char createClientsChoices[3][22] = {"Nome: ", "CPF: ", "Saldo: "};

	for (int i = 0; i < 3; i++)
	{

		mvwprintw(createclientwin, 2 + i, 1, "%s", createClientsChoices[i]);
		wattroff(createclientwin, A_REVERSE);
		wrefresh(createclientwin);
	}

	echo();
	wmove(createclientwin, 2, 6);
	wgetnstr(createclientwin, c.name, 12);

	wmove(createclientwin, 3, 5);
	wgetnstr(createclientwin, c.cpf, 11);

	mvwscanw(createclientwin, 4, 7, "%f", &c.balance);

	getchar();
	refresh();

	c.id = l->size + 1;
	write_client_r(filename, &c, l);

	destroy_win(createclientwin);
	clientsMenu(l, f, yMax, xMax);
}

void viewClientsMenu(list *l, fila *f, int yMax, int xMax, int skip)
{
	WINDOW *viewclientwin;

	getmaxyx(stdscr, yMax, xMax);
	viewclientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(viewclientwin, 0, 0);
	wrefresh(viewclientwin);

	keypad(viewclientwin, true);
	mvwprintw(viewclientwin, 1, 1, "ID\tNome\tCPF\t\tSaldo");
	wattroff(viewclientwin, A_REVERSE);
	wrefresh(viewclientwin);
	refresh();
	int starty = 1;
	int startx = 1;

	int r;

	if (l->size > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			struct node *n = get(*l, i + skip);
			if (n != NULL)
			{
				client cl = n->c;
				wattroff(viewclientwin, A_REVERSE);
				wmove(viewclientwin, starty + (i + 1), startx);
				wprintw(viewclientwin, "%d  %s\t%s\t%3.2f", cl.id, cl.name,
						cl.cpf, cl.balance);
				wattroff(viewclientwin, A_REVERSE);
				wrefresh(viewclientwin);
				n = n->next;
			}
		}
	}
	else
	{
		mvwprintw(viewclientwin, 2, 1, "Nenhum cliente registrado");
	}
	
	int quit = 0;
	while(!quit)
	{
		r = wgetch(viewclientwin);
		switch(r)
		{
			case KEY_UP:
				gSkip = gSkip > 0 ? gSkip - 5 : 0;
				viewClientsMenu(l, f, yMax, xMax, gSkip);
				break;
			case KEY_DOWN:
				gSkip = gSkip + 5;
				viewClientsMenu(l, f, yMax, xMax, gSkip);
				break;
			case 10:			
				quit = 1;		
				destroy_win(viewclientwin);
				clientsMenu(l, f, yMax, xMax);
				break;
		}
	}
	gSkip = 0;

	destroy_win(viewclientwin);
	clientsMenu(l, f, yMax, xMax);
}

void clientsMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *clientwin;

	clientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(clientwin, 0, 0);
	wrefresh(clientwin);

	keypad(clientwin, true);
	char clientsChoices[3][22] = {"Criar um Cliente", "Listar Clientes", "Voltar"};
	int clientChoice, highlight = 0, clientOption, aux = 0;

	while (!aux)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == highlight)
				wattron(clientwin, A_REVERSE);
			mvwprintw(clientwin, i + 2, 1, "\t%s", clientsChoices[i]);
			wattroff(clientwin, A_REVERSE);
			wrefresh(clientwin);
		}
		clientChoice = wgetch(clientwin);

		switch (clientChoice)
		{
		case KEY_UP:
			highlight--;
			if (highlight == -1)
				highlight = 2;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3)
				highlight = 0;
			break;
		case 10:
			clientOption = highlight + 1;
			switch (clientOption)
			{
			case 1:
				refresh();
				destroy_win(clientwin);
				createClientsMenu(l, f, yMax, xMax);
				break;
			case 2:
				refresh();
				destroy_win(clientwin);
				viewClientsMenu(l, f, yMax, xMax, 0);
				break;
			case 3:
				refresh();
				destroy_win(clientwin);
				mainMenu(l, f, yMax, xMax);
				aux = 1;
				break;
			default:
				aux = 1;
				refresh();
				break;
			}
		default:
			break;
		}
	}
}

void mainMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *win;

	win = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(win, 0, 0);
	wrefresh(win);

	keypad(win, true);

	char choices[3][9] = {"Clientes", "Fila", "Sair"};
	int choice, highlight = 0, option, aux = 0;
	wrefresh(win);
	while (!aux)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == highlight)
				wattron(win, A_REVERSE);

			mvwprintw(win, i + 2, 1, "\t%s", choices[i]);
			wattroff(win, A_REVERSE);
			wrefresh(win);
		}
		choice = wgetch(win);
		switch (choice)
		{
		case KEY_UP:
			highlight--;
			if (highlight == -1)
				highlight = 2;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3)
				highlight = 0;
			break;
		case 10:
			option = highlight + 1;
			switch (option)
			{
			case 1:
				refresh();
				destroy_win(win);
				clientsMenu(l, f, yMax, xMax);
				break;
			case 2:
				refresh();
				destroy_win(win);
				rowMenu(l, f, yMax, xMax);
				break;
			case 3:
				refresh();
				destroy_win(win);
				aux = 1;
				endwin();
				exit(0);
				break;
			default:
				refresh();
				aux = 1;
				break;
			}
		}
	}
	refresh();
	endwin();
	return;
}

void printMenu(list *l, fila *f)
{
	int yMax, xMax;
	initscr();
	noecho();
	cbreak();
	getmaxyx(stdscr, yMax, xMax);
	mainMenu(l, f, yMax, xMax);
	refresh();
	endwin();
}
