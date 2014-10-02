amazon_warehouse
================
Ivan Cherem
Program Written in 2012

COMPILE:
clang++ -g -Wall -Wextra Retriever.cpp main.cpp Packager.cpp Warehouse.cpp

RUN:
./a.out < input_#.txt

This program simulates an Amazon Warehouse by simulating Retrievers and
Packagers. Two simulations run and waiting times under both conditions are
reported. One simulates  Amazon with Amazon Prime and the other simulates
Amazon without it.
Amazon prime allows customers  to become "supreme customers." Supreme
customers will jump to the front of the queue.
