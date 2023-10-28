// ast.h
// structs for making abstract syntax tree
#ifndef AST_H
#define AST_H

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char data);
int evaluateTree(TreeNode* root);
TreeNode* buildSyntaxTree(char* expression, int start, int end);

#endif // AST_H
