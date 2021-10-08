#include <stdio.h>
#include <ncurses.h>

#include "client.h"
#include "list.h"

int count = 0;

int main()
{

    list l; init(&l);

	client c;

    for(int i = 0; i < 3; i++)
    {
        puts("Nome: ");
        scanf("%s", c.name); getchar();
        puts("CPF: ");
        scanf("%s", c.cpf); getchar();
        puts("Saldo: ");
        scanf("%lf", &c.balance); getchar();

        c.id = ++count;

        push_back(&l, c);
    }

    for(int i = 0; i < l.size; i++)
    {
        print_client(get(l, i)->c);
    }

	return 0;
}
