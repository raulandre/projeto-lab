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

	printMenu(&l);

	return 0;
}
