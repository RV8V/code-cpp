#!/bin/bash

g++ -c lesson4.constructor.cpp -o lesson4.constructor.o
g++ -c main.cpp -o main.o
g++ main.o lesson4.constructor.o -o a.out
rm -rf *.o
