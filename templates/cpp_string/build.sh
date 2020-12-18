#!/bin/bash

g++ -c cpp_string.cpp -o cpp_string.o
g++ -c main.cpp -o main.o
g++ main.o cpp_string.o -o a.out
rm -rf *.o
