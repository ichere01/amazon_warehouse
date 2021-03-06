// Packager queues will take in orders that have been retrieved.
// The head of each packager is the Order being packaged.

#ifndef  PACKAGER_H
#define  PACKAGER_H
#include "Order.h"


class Packager{

public:

    Packager();
    
    // Add a normal order to the back of the queue
    void addNormal(Order toAdd);

    // Add a supreme order to appropriate place. If no other supremes in the
    // queue, it will be added at the front. If other supremes in the queue,
    // it will be added after the last supreme.
    void addSupreme (Order toAdd);
    
    // Will update the package time and total wait time of order at the head
    // Will call Remove when packing is done 
    bool isPacked ();

    // Removes orders that have been packaged from queue."Sends" the package
    void Remove();

    bool isEmpty();

    void print();

    bool isWorking;

    Order remove();

     // total wait time for normal customers 
    int getnormalWait();

    // wait time for supremes. If no supremes on queue then its 0
    int getsupremeWait();

    int normalWait;
    int supremeWait;
private:
    Order* head;  // front of queue
    Order* tail; // back of queue

    int time;

};
#endif
