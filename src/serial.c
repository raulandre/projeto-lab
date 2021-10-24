#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "serial.h"
#include "list.h"
#include "client.h"

bool file_exists(const char *filename)
{
	return access(filename, F_OK) == 0 ? true : false;
}

int count_lines(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	int count = 0;
	char c;

	if(fp == NULL) return -1;

	for(c = getc(fp); c != EOF; c = getc(fp))
		if(c == '\n')
			count++;
	fclose(fp);
	return count;
}

int getmaxlen(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	int MAX_SIZE = 0, CURRENT_SIZE = 0;
	char c;

	if(fp == NULL) return -1;

	for(c = getc(fp); c != EOF; c = getc(fp))
	{
		if(c == '\n')
		{
			MAX_SIZE = CURRENT_SIZE > MAX_SIZE ? CURRENT_SIZE : MAX_SIZE;
			CURRENT_SIZE = 0;
		}
		else
			CURRENT_SIZE++;
	}

	fclose(fp);

	return MAX_SIZE;
}

void create_file(const char *filename)
{
	FILE *fp = fopen(filename, "w");
	fclose(fp);
}

void load_data(list *l, const char *filename)
{
	int LINE_SIZE = getmaxlen(filename);
	int LINE_COUNT = count_lines(filename);
	char *line = (char*) malloc(sizeof(char) * LINE_SIZE);

	FILE *fp = fopen(filename, "r");
	if(fp == NULL) return;

	client cl;

	char c;
	int pos = 0;
	for(int i = 0; i < LINE_COUNT; i++)
	{
		for(c = getc(fp); c != EOF; c = getc(fp))
		{
			if(c == '\n')
			{
				cl = parse_client(line);
				push_back(l, cl);
				memset(line, 0, strlen(line));
				pos = 0;
			}
			else
			{
				line[pos] = c;
				pos++;
			}
		}
	}

	free(line);

	fclose(fp);
}

client parse_client(char *line)
{
	char *aux = strtok(line, ",");
	client cl;

	int i = 0;
	while(aux)
	{
		if(i == 0)
		{
			cl.id = atoi(aux);
		}
		else if(i == 1)
		{
			strcpy(cl.name, aux);
		}
		else if(i == 2)
		{
			strcpy(cl.cpf, aux);
		}
		else
		{
			cl.balance = atof(aux);
		}
		i = (i == 3 ? 0 : i+1);
		aux = strtok(NULL, ",");
	}

	return cl;
}
