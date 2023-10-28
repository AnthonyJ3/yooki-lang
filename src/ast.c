// ast.c
// program to create and evaluate ast
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

// create a new tree node
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// evaluate the syntax tree
int evaluateTree(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->data - '0'; // convert character to integer
    }

    int leftValue = evaluateTree(root->left);
    int rightValue = evaluateTree(root->right);

    //dividing and parenthesis are currently an issue
    //need to figure out core data structs & representations
    switch (root->data) {
        case '+':
            //printf("%d\n", leftValue + rightValue);
            return leftValue + rightValue;
        case '-':
            //printf("%d\n", leftValue - rightValue);
            return leftValue - rightValue;
        case '*':
            //printf("%d\n", leftValue * rightValue);
            return leftValue * rightValue;
        case '/':
            //printf("%d\n", leftValue / rightValue);
            // maybe replace with bitshift?
            return leftValue / rightValue;
        default:
            printf("Invalid operator: %c\n", root->data);
            exit(1);
    }
}

// build a syntax tree from a given expression
// currently broken lol
TreeNode* buildSyntaxTree(char* expression, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int parenthesesCount = 0;
    int position = -1;

    //bug somewhere when evaluating multiple parentheses
    for (int i = end; i >= start; i--) {
        if (expression[i] == ')') {
            parenthesesCount++;
        } else if (expression[i] == '(') {
            parenthesesCount--;
        } else if (parenthesesCount == 0 &&
                   (expression[i] == '+' || expression[i] == '-')) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        for (int i = end; i >= start; i--) {
            if (expression[i] == ')') {
                parenthesesCount++;
            } else if (expression[i] == '(') {
                parenthesesCount--;
            } else if (parenthesesCount == 0 &&
                       (expression[i] == '*' || expression[i] == '/')) {
                position = i;
                break;
            }
        }
    }

    if (position == -1) {
        if (expression[start] == '(' && expression[end] == ')') {
            return buildSyntaxTree(expression, start + 1, end - 1);
        }
        return createNode(expression[start]);
    }

    TreeNode* root = createNode(expression[position]);
    root->left = buildSyntaxTree(expression, start, position - 1);
    root->right = buildSyntaxTree(expression, position + 1, end);

    return root;
}