#ifndef CLIENT_H
#define CLIENT_H

typedef struct
{
	int id;
	char name[30];
	char cpf[11];
	double balance;
} client;

void print_client(client);

#endif //CLIENT_H
