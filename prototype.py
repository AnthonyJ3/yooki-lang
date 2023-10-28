class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def evaluate_tree(root):
    if root is None:
        return 0

    if root.left is None and root.right is None:
        return int(root.data)

    left_value = evaluate_tree(root.left)
    right_value = evaluate_tree(root.right)

    if root.data == '+':
        return left_value + right_value
    elif root.data == '-':
        return left_value - right_value
    elif root.data == '*':
        return left_value * right_value
    elif root.data == '/':
        return left_value / right_value
    else:
        print("Invalid operator: ", root.data)
        exit(1)

def build_expression_tree(expression, start, end):
    if start > end:
        return None

    parentheses_count = 0
    position = -1

    for i in range(end, start - 1, -1):
        if expression[i] == ')':
            parentheses_count += 1
        elif expression[i] == '(':
            parentheses_count -= 1
        elif parentheses_count == 0 and (expression[i] == '+' or expression[i] == '-'):
            position = i
            break

    if position == -1:
        for i in range(end, start - 1, -1):
            if expression[i] == ')':
                parentheses_count += 1
            elif expression[i] == '(':
                parentheses_count -= 1
            elif parentheses_count == 0 and (expression[i] == '*' or expression[i] == '/'):
                position = i
                break

    if position == -1:
        if expression[start] == '(' and expression[end] == ')':
            return build_expression_tree(expression, start + 1, end - 1)
        return TreeNode(expression[start])

    root = TreeNode(expression[position])
    root.left = build_expression_tree(expression, start, position - 1)
    root.right = build_expression_tree(expression, position + 1, end)

    return root

expression = "2*(3+4)-6/2"
root = build_expression_tree(expression, 0, len(expression) - 1)
result = evaluate_tree(root)
print("Result:", result)
