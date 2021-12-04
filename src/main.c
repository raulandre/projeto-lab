#include "mainmenu.h"
#include "client.h"
#include "list.h"
#include "fila.h"
#include "serial.h"

#define filename "clients.dat"

int main()
{
	list l; init(&l);
	fila f; cria(&f);

	if(!file_exists(filename))
		create_file(filename);

	load_data(&l, filename);

	printMenu(&l, &f);

	return 0;
}
