#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 255

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

// Helper functions

Token char_to_token(char c);
char* tk_to_str(Token tk);
void print_tk_out();


// Main functions

char peek();
void drop();
void emit(Token tk);

int lex_init();
int lex_var_or_id_or_kw(char* lexemme);
int lex(char* s);


int main(int argc, char* argv[]) {
    if(argc != 2) {printf("Supply one argument with string to be recognised.\n") ;return -1;}

    lex(argv[1]);
    print_tk_out();

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

int lex(char* s) {
    idx = 0;
    tidx = 0;
    input = s;
    lex_init();
}

int lex_init() {
    char c = peek();
    if (c == '\0') {
        emit(END); 
        return 0;
    }else {
        if(c == '(' || c == ')' || c == '=' || c == ',') {
            drop();
            emit(char_to_token(c));
            lex_init();
        }else if (c == '\n' || c == '\r' || c == ' ' || !isprint(c))
        {
            drop();
            lex_init();
        }else if (isalpha(c))
        {
            char* lexemme = calloc(100, sizeof(char));
            lexemme[0] = '\0';
            lex_var_or_id_or_kw(lexemme);
            free(lexemme);
        }else {
            return -1;
        }
    }
}

int lex_var_or_id_or_kw(char* lexemme) {
    char c = peek();
    if (isalpha(c)) {
        size_t len = strlen(lexemme);
        lexemme[len] = c;
        lexemme[len + 1] = '\0';
        drop();
        lex_var_or_id_or_kw(lexemme);
    }else {
        if(strcmp(lexemme, "def") == 0) {
            emit(DEFINE);
        }else if (islower(lexemme[0]))
        {
            emit(VAR);
        }else {
            emit(IDENT);
        }
    }
    lex_init();
}


Token char_to_token(char c) {
    switch (c)
    {
    case '(':
        return LPAREN;
    case ')':
        return RPAREN;
    case '=':
        return EQUALS;
    case ',':
        return COMMA;    
    default:
        return END;
    }
}

char* tk_to_str(Token tk) {
    switch (tk)
    {
    case IDENT:
        return "IDENT";
    case VAR:
        return "VAR";
    case LPAREN:
        return "LPAREN";
    case RPAREN:
        return "RPAREN";
    case DEFINE:
        return "DEFINE";
    case COMMA:
        return "COMMA";
    case EQUALS:
        return "EQUALS";
    case END:
        return "END";
    default:
        return "END";
    }
}

void print_tk_out() {
    for(int i = 0; i < MAX_LEN; i++) {
        if (output[i] == END) {
            printf("END\n");
            return;
        }
        printf("%s, ", tk_to_str(output[i]));
    }
}