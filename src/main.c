#include <stdio.h>
#include <ncurses.h>

#include "client.h"
#include "list.h"
#include "queue.h"

int count = 0;

int main()
{

    list l;
    init(&l);
    queue q;
    initq(&q);

    client c;
    int r;

    puts("Nome: ");
    r = scanf("%s", c.name);
    getchar();
    puts("CPF: ");
    r = scanf("%s", c.cpf);
    getchar();
    puts("Saldo: ");
    r = scanf("%lf", &c.balance);
    getchar();

    c.id = ++count;

    push_back(&l, c);

    addq(&q, c);
    print_client(q.end->c);

    return 0;
}
