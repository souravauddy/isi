#include "parser.h"

const int MAX_ARGUMENTS = (int) 100;
const char *DELIMETER = " ;\n";
const char *SERIAL_OPERATOR = "&&";
const char *PARALLEL_OPERATOR = "&&&";
const char *BACKGROUND_OPERATOR = "&";
const char *EITHER_OPERATOR = "||";

void init_parser(parser *argument_parser) {
    argument_parser->number_of_tokens = 0;
    argument_parser->tokens = (char **) malloc(MAX_ARGUMENTS * sizeof(char *));
    // argument_parser->_has_parallel_operator = argument_parser->_has_serial_operator = false;
}

void parse(parser *argument_parser, char *line) {
    char *token = strtok(line, DELIMETER);

    for (argument_parser->number_of_tokens = 0; token != NULL; argument_parser->number_of_tokens++) {
        // argument_parser->_has_serial_operator |= !strcmp(token, "&&");
        // argument_parser->_has_parallel_operator |= !strcmp(token, "&&&");
        argument_parser->tokens[argument_parser->number_of_tokens] = token;
        token = strtok(NULL, DELIMETER);
    }
}

void print_parsed_arguments(const parser *argument_parser) {
    for (int i = 0; i < argument_parser->number_of_tokens; i++) {
        assert(argument_parser->tokens[i]);
        printf("%s\n", argument_parser->tokens[i]);
    }
    puts("");
}

void free_parser(parser *argument_parser) {
    free(argument_parser->tokens);
    free(argument_parser);
}
