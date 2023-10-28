#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

(
    pushd "$SCRIPT_DIR"
    # Compile C source files
    gcc -o ../interpreter.exe ../src/main.c ../src/ast.c -g
    # gcc -o ../interpreter.exe ../src/main.c ../src/ast.c -g

    # Check for compilation errors
    if [ $? -eq 0 ]; then
        echo "Compilation successful."
    else
        echo "Compilation failed."
    fi
    popd
)