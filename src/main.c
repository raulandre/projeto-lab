#include "mainmenu.h"
#include "client.h"
#include "list.h"
#include "queue.h"
#include "serial.h"

#define filename "clients.dat"

int main()
{
	list l; init(&l);

	if(!file_exists(filename))
		create_file(filename);

	load_data(&l, filename);

	client cl = { .id = 1, .name = "Main", .cpf = "12345678912", .balance = 0.0f };

	write_client(filename, &cl);

    printMenu();

	return 0;
}
