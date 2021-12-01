#include <stdio.h>
#include <stdlib.h>
#include "mainmenu.h"
#include "client.h"
#include "serial.h"

#define filename "clients.dat"

client c;

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

void rowViewMenu (list *l, fila *f, int yMax, int xMax)
{	
	WINDOW *viewclientwin;

	getmaxyx(stdscr, yMax, xMax);
	viewclientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(viewclientwin, 0, 0);
	wrefresh(viewclientwin);

	keypad(viewclientwin, true);
	mvwprintw(viewclientwin, 1, 1, " Nome\t\tCPF\t\tSaldo");
	wattroff(viewclientwin, A_REVERSE);
	wrefresh(viewclientwin);
	refresh();
	int starty = 1;
	int startx = 1;


	struct no *n = f->inicio;
	/*if (n != NULL)
	  {
	  client cl = n->c;
	  wattroff(viewclientwin, A_REVERSE);
	  wmove(viewclientwin, starty + (i + 1), startx);
	  wprintw(viewclientwin, "%s\t%s\t%.2f", cl.name,
	  cl.cpf, cl.balance);
	  wattroff(viewclientwin, A_REVERSE);
	  wrefresh(viewclientwin)
	  }
	  n = n->next;*/
	if (n != NULL)
	{
		int i = 0;

		do
		{
			client cl = n->c;

			wattroff(viewclientwin, A_REVERSE);
			wmove(viewclientwin, starty + (i + 1), startx);
			wprintw(viewclientwin, "%s\t%s\t%.2f", cl.name,
					cl.cpf, cl.balance);
			wattroff(viewclientwin, A_REVERSE);
			wrefresh(viewclientwin);
				n = n-> prox;
				i++;

		} while (n != NULL);
	}

	getch();
	destroy_win(viewclientwin);
	clientsMenu(l, f, yMax, xMax);
}
void rowMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *rowwin;
	
	rowwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(rowwin, 0, 0);
	wrefresh(rowwin);

	keypad(rowwin, true);
	char rowChoices[4][40] = {"Mostrar a Fila", "Adicionar", "Chamar o Proximo", "Voltar"};
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
				destroy_win (rowwin);
				rowViewMenu(l, f, yMax, xMax);
				break;
			case 2:
				break;
			case 3:
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

void createClientsMenu (list *l, fila *f, int yMax, int xMax)
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

		mvwprintw(createclientwin, 1 + i, 1, "%s", createClientsChoices[i]);
		wattroff(createclientwin, A_REVERSE);
		wrefresh(createclientwin);
	}

	echo();
	wmove(createclientwin, 1, 6);
	wgetnstr(createclientwin, c.name, 30);

	wmove(createclientwin, 2, 5);
	wgetnstr(createclientwin, c.cpf, 11);

	mvwscanw(createclientwin, 3, 7, "%f", &c.balance);

	getchar();
	refresh();

	c.id = l->size + 1;
	write_client_r(filename, &c, l);

	destroy_win(createclientwin);
	clientsMenu(l, f, yMax, xMax);
}

void viewClientsMenu(list *l, fila *f, int yMax, int xMax)
{
	WINDOW *viewclientwin;

	getmaxyx(stdscr, yMax, xMax);
	viewclientwin = create_newwin(8, 40, (yMax / 2) - 4, (xMax / 2) - 20);
	refresh();
	box(viewclientwin, 0, 0);
	wrefresh(viewclientwin);

	keypad(viewclientwin, true);
	mvwprintw(viewclientwin, 1, 1, " Nome\t\tCPF\t\tSaldo");
	wattroff(viewclientwin, A_REVERSE);
	wrefresh(viewclientwin);
	refresh();
	int starty = 1;
	int startx = 1;

	if (l->size > 0)
	{
		for (int i = 0; i < l->size; i++)
		{
			struct node *n = get(*l, i);
			if (n != NULL)
			{
				client cl = n->c;
				wattroff(viewclientwin, A_REVERSE);
				wmove(viewclientwin, starty + (i + 1), startx);
				wprintw(viewclientwin, "%s\t%s\t%.2f", cl.name,
						cl.cpf, cl.balance);
				wattroff(viewclientwin, A_REVERSE);
				wrefresh(viewclientwin);
			}
			n = n->next;
		}
	}
	else
	{
		mvwprintw(viewclientwin, 1, 1, "nao tem cliente");
	}
	getch();
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
				viewClientsMenu(l, f, yMax, xMax);
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
				aux =1;
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
	aux =1;
	refresh();
	endwin();	
	return;
}

void printMenu(list *l, fila *f)
{
	initscr();
	noecho();
	cbreak();
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	mainMenu(l, f, yMax, xMax);
	refresh();
	endwin();
}
