// assigns a token type to each character in the input expression
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OPERATOR,  // +, -, *, /
    NUMBER,    // 0-9
    CHAR,      // a-z, A-Z
    SYMBOL,    // !, @, #, $, %, ^, &, _, =, +, [, ], {, }, |, <, >, ?, ~
    LPAREN,    // ( 
    RPAREN,    // ) 
    QUOTE,     // ", '
    COMMENT,   // #
    MACRO,     // :
    ENDLINE,   // ;
    DOT,       // .
    COMMA,     // ,
    KEYWORD,   // if, else, etc.
    UNDEFINED, // anything else
    END        
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token; 

Token createToken(TokenType type, char* value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

TokenType checkKeywords(char* string) {
    switch (*string) {
        //add keywords with enums maybe
        default:
            return UNDEFINED;
    }
}

int isOperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;
        default:
            return 0;
    }
}

int isAlphabetical(char c) {
    switch (c) {
        case 'a'...'z':
        case 'A'...'Z':
            return 1;
        default:
            return 0;
    }
}

Token* tokenize(char* expression) {
    Token* tokens = (Token*)malloc(strlen(expression) * sizeof(Token));
    //make sure not leaking memory
    int tokenCount = 0;
    for (int i = 0; i < strlen(expression); i++) {
        if (isspace(expression[i])) {
            // Skip spaces for now
            continue;
        } else if (isOperator(expression[i])) {
            char* operator = (char*)malloc(2);
            operator[0] = expression[i];
            operator[1] = '\0';
            tokens[tokenCount++] = createToken(OPERATOR, operator);
        } else if (isdigit(expression[i])) {
            // Parse numbers
            int j = i;
            while (isdigit(expression[j])) {
                j++;
            }
            char* number = (char*)malloc(j - i + 1);
            strncpy(number, expression + i, j - i);
            number[j - i] = '\0';
            tokens[tokenCount++] = createToken(NUMBER, number);
            i = j - 1;
        } else if (isAlphabetical(expression[i])) {
            // Parse characters
            int j = i;
            while (isAlphabetical(expression[j])) {
                j++;
            }
            char* string = (char*)malloc(j - i + 1);
            strncpy(string, expression + i, j - i);
            string[j - i] = '\0';
            tokens[tokenCount++] = createToken(checkKeywords(string), string);
            i = j - 1;
        }
        // check for reserved keywords
    }
    tokens[tokenCount] = createToken(END, NULL);
    return tokens;
}

int main() {
    char expression[] = "2 + 3 * 4 - 1";
    Token* tokens = tokenize(expression);

    for (int i = 0; tokens[i].type != END; i++) {
        printf("Token Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token values
    }

    free(tokens);  // Free the tokens array

    return 0;
}
