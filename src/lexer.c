#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum {
    TOKEN_OPERATOR,
    TOKEN_NUMBER,
    TOKEN_END
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char* value;
} Token;

// Function to initialize a token
Token createToken(TokenType type, char* value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to tokenize an input expression
Token* tokenize(char* expression) {
    int length = strlen(expression);
    Token* tokens = (Token*)malloc(length * sizeof(Token));  // Assuming each character is a token

    int tokenCount = 0;
    for (int i = 0; i < length; i++) {
        if (isspace(expression[i])) {
            // Skip spaces
            continue;
        } else if (isOperator(expression[i])) {
            // Operators are single-character tokens
            char* operator = (char*)malloc(2);
            operator[0] = expression[i];
            operator[1] = '\0';
            tokens[tokenCount++] = createToken(TOKEN_OPERATOR, operator);
        } else if (isdigit(expression[i])) {
            // Parse numbers
            int j = i;
            while (isdigit(expression[j])) {
                j++;
            }
            char* number = (char*)malloc(j - i + 1);
            strncpy(number, expression + i, j - i);
            number[j - i] = '\0';
            tokens[tokenCount++] = createToken(TOKEN_NUMBER, number);
            i = j - 1;
        } else {
            // Handle other characters as needed
            // For simplicity, this example doesn't handle other character types
        }
    }

    // Add an end token
    tokens[tokenCount] = createToken(TOKEN_END, NULL);

    return tokens;
}

int main() {
    char expression[] = "2 + 3 * 4 - 1";
    Token* tokens = tokenize(expression);

    for (int i = 0; tokens[i].type != TOKEN_END; i++) {
        printf("Token Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token values
    }

    free(tokens);  // Free the tokens array

    return 0;
}
