#ifndef SERIAL_H
#define SERIAL_H

#include "list.h"
#include "client.h"
#include <stdbool.h>

#define CLIENT_FORMAT "%d,%[^,],%[^,],%lf"

bool file_exists(const char*);
int count_lines(const char*);
int getmaxlen(const char*);
void create_file(const char*);
client parse_client(char*);
void load_data(list*, const char*);

#endif
