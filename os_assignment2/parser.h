#ifndef _PARSER_

#define _PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

struct parser {
    char **tokens;
    int number_of_tokens;
    // bool _has_serial_operator, _has_parallel_operator;
};

typedef struct parser parser;

void init_parser(parser *);
void parse(parser *, char *);
void print_parsed_arguments(const parser *);
void free_parser(parser *);

#endif