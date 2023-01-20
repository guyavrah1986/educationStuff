#!/bin/bash

echo "START compilation script"
rm c.o main.o main.o
g++ -Wall -c -o main.o -std=c++98 main.cpp
gcc -Wall -c -o c.o -std=c90 c.c
g++ -o main.out main.o c.o

echo "END compilation script"
