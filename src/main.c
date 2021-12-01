#include "mainmenu.h"
#include "client.h"
#include "list.h"
#include "queue.h"
#include "serial.h"

#define filename "clients.dat"

int main()
{
	list l; init(&l);
	fila f; f.inicio = NULL; f.fim = NULL;
	client c = {.id=2, .name="BielGAAAAy", .cpf="66666666666"};
	insere (&f, c);
	if(!file_exists(filename))
		create_file(filename);

	load_data(&l, filename);

	printMenu(&l, &f);

	return 0;
}
