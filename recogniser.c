#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_eat(tk) if(eat(tk)) {if(debug) {printf("Error: Failed parsing token %s.\n", tk_to_str(tk));} return -1;}
#define handle_parse(parser, context) if(parser()) {if(debug) {printf("Error: Failed parsing in %s.\n", context);} return -1;}

// Helper functions

Token peek();
int eat(Token tk);

// Parsing functions

int parse_cmd();
int parse_exp();
int parse_explist();
int parse_explist_prime();

int parse(char* s);

Token* input;
int debug = 0;

int main(int argc, char* argv[]) {
    char* s;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug = 1;
            printf("Debug: ON\n");
        } else {
            s = argv[i];
        }
    }
    return parse(s);
}

Token peek() {
    return input[0];
}

int eat(Token tk) {
    if(peek() == tk) {
        input++;
        return 0;
    }
    //printf("Error: token %s != %s next in input.\n", tk_to_str(tk), tk_to_str(peek()));
    return -1;
}

int parse_cmd() {
    switch (peek())
    {
    case DEFINE:
        handle_eat(DEFINE);
        handle_eat(IDENT);
        handle_eat(LPAREN);
        handle_parse(parse_explist, "parse_explist");
        handle_eat(RPAREN);
        handle_eat(EQUALS);
        handle_parse(parse_exp, "parse_exp");
        handle_eat(END);
        return 0;
    case IDENT:
        handle_parse(parse_exp, "parse_exp");
        handle_eat(END);
        return 0;
    case VAR:
        handle_parse(parse_exp, "parse_exp");
        handle_eat(END);
        return 0;
    default:
        return -1;
    }
    return -1;
}

int parse_exp() {
    switch (peek())
    {
    case IDENT:
        handle_eat(IDENT);
        handle_eat(LPAREN);
        handle_parse(parse_explist, "parse_explist");
        handle_eat(RPAREN);
        return 0;
    case VAR:
        handle_eat(VAR);
        return 0;
    default:
        return -1;
    }
    return -1;
}

int parse_explist() {
    switch (peek())
    {
    case IDENT:
        handle_parse(parse_exp, "parse_exp");
        handle_parse(parse_explist_prime, "parse_explist_prime");
        return 0;
    case RPAREN:
        return 0;
    case VAR:
        handle_parse(parse_exp, "parse_exp");
        handle_parse(parse_explist_prime, "parse_explist_prime");
        return 0;
    default:
        return -1;
    }
    return -1;
}

int parse_explist_prime() {
    switch (peek())
    {
    case RPAREN:
        return 0;
    case COMMA:
        handle_eat(COMMA);
        handle_parse(parse_exp, "parse_exp");
        handle_parse(parse_explist, "parse_explist");
        return 0;
    default:
        return -1;
    }
    return -1;
}

int parse(char* s) {
    input = lex(s);
    if(parse_cmd()) {
        printf("False\n");
        return -1;
    }else{
        printf("True\n");
        return 0;
    }
}