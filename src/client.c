#include <stdio.h>
#include "client.h"

void print_client(client c)
{
	puts("==========================");
	printf("ID: %d\n", c.id);
	printf("Nome: %s\n", c.name);
	printf("CPF: %s\n", c.cpf);
	printf("Saldo: %.2f\n", c.balance);
	puts("==========================");
}
