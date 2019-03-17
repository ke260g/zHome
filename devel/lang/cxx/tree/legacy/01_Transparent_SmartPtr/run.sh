#!/bin/bash
g++ -std=c++11 bTree.cpp && ./a.out
dot -Tpng -o bTreeDot.png bTreeDot.dot
echo show the bTreeDot.png with some tools
