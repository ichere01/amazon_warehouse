// Ivan Cherem M. 

// The retriever queue will act as the warehouse in which Orders are going to
// be initially placed. The head of the queue will be the item being retrieved.
// After retrieval, Orders are sent to Packaging.

#ifndef RETRIEVER_H
#define RETRIEVER_H
#include "Order.h"

class Retriever{

public:

    // constructor
    Retriever();
    
    // places an order in the back of the queue
    void add(Order toAdd);

    bool isEmpty();

    // has the queue finished processing orders?
    bool isWorking;

    // updates how long an item has been in retrieval and when its ready to be  
    // packaged will send a bool that tells the manager (in main) to send it to
    // packaging
    bool isFetched();

    // removes order at front of the queue, will only be called by manager
    // function when Order is ready to be sent to packaging    
    Order remove();

    // prints basic information on all elements in queue
    void print();

    // fill queue from cin
    void fillQueue();

    void copyOrdersFromList(Retriever toCopy);

    Order* getHead();

private:

    Order* head;
    Order* tail;

    // keeps track of time passed since simulation;
    int time;


 

};
#endif


    
