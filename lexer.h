#ifndef LEXER_H
#define LEXER_H

typedef enum {
    IDENT,
    VAR,
    LPAREN,
    RPAREN,
    DEFINE,
    COMMA,
    EQUALS,
    END
} Token;

Token char_to_token(char c);
char* tk_to_str(Token tk);

Token* lex(char* s);

void print_tk_out();

#endif