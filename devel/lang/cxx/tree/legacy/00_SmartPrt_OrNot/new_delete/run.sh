#!/bin/bash
g++ -std=c++11 bTree.cpp && ./a.out
dot -Tpng -o bTreeDot.png bTreeDot.dot
echo "now you can display the bTreeDot.png"
echo "you are suggested to detect memory overflow"
echo -e "example: \$(sh_prompt)>_ valgrind --leak-check=summary --tool=memcheck ./a.out"
