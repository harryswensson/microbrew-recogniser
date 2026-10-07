#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 100

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

int idx;
char* input;
int tidx;
Token output[MAX_LEN];

char peek();
void drop();
void emit(Token tk);


int main(int argc, char* argv[]) {
    if(argc > 2) {printf("Too many arguments.\n") ;return -1;}

    idx = 0;
    tidx = 0;
    input = argv[1];


    printf("Recognising: %s\n", input); 
    return 0;
}

char peek() {
    return input[idx];
}

void drop() {
    input++;
}

void emit(Token tk) {
    output[tidx] = tk;
    tidx++;
}

