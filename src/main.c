// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

char* readFile(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return NULL;
    }

    const char *filename = argv[1];

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening the file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_contents = (char *)malloc(file_size + 1);

    if (file_contents == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(file_contents, 1, file_size, file);

    if (read_size != file_size) {
        perror("Error reading the file");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';

    fclose(file);

    return file_contents;
}

int main(int argc, char *argv[]) {

    // Need to add usage printout, and line by line mode

    // read input file
    char* file_contents = readFile(argc, argv);

    // pass into lexer & return result
    TreeNode* syntax_tree_root = buildSyntaxTree(file_contents, 0, strlen(file_contents));
    int result = evaluateTree(syntax_tree_root);

    // print interpreted result to console
    printf("%d\n", result);

    free(file_contents);
    free(syntax_tree_root);
    return 0;
}