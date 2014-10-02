Ivan Cherem
Program Written in 2012

COMPILE:
clang++ -g -Wall -Wextra Retriever.cpp main.cpp Packager.cpp Warehouse.cpp

RUN:
./a.out < input_#.txt

This program simulates an Amazon Warehouse, with Retrievers and Packagers. 
Output consists of information about waiting time under two conditions: Amazon
with Amazon prime and Amazon without it. Amazon prime allows customers  to
become "supreme customers" and will jump to the from of the queue.
