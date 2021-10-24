#ifndef SERIAL_H
#define SERIAL_H

#include "list.h"
#include "client.h"
#include <stdbool.h>

#define CLIENT_FORMAT "%d,%s,%s,%.2f\n"

bool file_exists(const char*);
int count_lines(const char*);
int getmaxlen(const char*);
void create_file(const char*);
client parse_client(char*);
void load_data(list*, const char*);
void write_client(const char*, client*); //Apenas escreve o cliente
void write_client_r(const char*, client*, list*); //Escreve o cliente e adiciona na lista

#endif
