#include "retriever.h"

//#include <cstddef>
#include <cstdlib>
#include <iostream>
using namespace std;

Retriever::Retriever()
{
    head = NULL;
    tail = NULL;
    time = 0;
    isWorking = true;
}

// Will add and Order to the back of the Queue
void Retriever::add(Order toAdd)
{
    Order* newOrder = new Order;

    *newOrder = toAdd;

    if (isEmpty()){
	head = newOrder;
	tail = head;
    }

    tail -> next = newOrder;
    tail = newOrder;
    
    newOrder -> next = NULL;
}

// Will take an order from the front of the Queue
// To be called when Order is ready to send to packaging
Order Retriever::remove()
{
    if (isEmpty()){
	cerr << "Can't remove from empty list" << endl;
	exit(1);
    }
    Order toRemove = *head; // Create an Order to be returned
    Order* destroyer = head;
    head = head-> next;
    delete destroyer;
    return toRemove;
}

bool Retriever::isEmpty()
{
    return head == NULL;
}

// Prints information on Order at the head of the queue
// Notes: For testing purposes it can print out the whole queue by removing
// the comments
void Retriever::print()
{
    if (isEmpty()){
	cout << "Cant print from empty list" << endl;
	exit(1);
    }
    Order* iter = head;
    int S1min = head -> totalWaitSM1;
    int S2min = head -> totalWaitSM2;
    int S1max = head -> totalWaitSM1;
    int S2max = head -> totalWaitSM2;
    int S1total = 0;
    int S2total = 0;
    int S2totalSupreme = 0;
    int S2totalRegular = 0;
    
    
	int orderCounter = 0;
    while (iter != NULL){
	
	if (iter -> totalWaitSM1 < S1min)
	    S1min = iter -> totalWaitSM1;
	if (iter -> totalWaitSM2 < S2min)
	    S2min = iter -> totalWaitSM2;

	if (iter -> totalWaitSM1 > S1max)
	    S1max = iter -> totalWaitSM1;
	if (iter -> totalWaitSM2 > S2max)
	    S2max = iter -> totalWaitSM2;
	
	S1total += iter -> totalWaitSM1;
	S2total += iter -> totalWaitSM2;
	
	if (iter -> isSupreme)
	    S2totalSupreme += iter -> totalWaitSM2;
	else
	    S2totalRegular += iter -> totalWaitSM2;
	
		
	cout << "Order " << iter -> ID << " for ";

	   if (iter -> isSupreme)
		cout << "supreme customer ";
	    else
		cout << "regular customer ";
	    
	    cout  << "arrived at time " << iter -> arrivalTime
		  << endl << "fetch time " << iter -> fetchTime
		  << " minutes, pack time " << iter -> packTime
		  << endl
		//  << "the order was added to packaging queue at time "
		// << iter -> arrivalPackaging << endl
		  << "elapsed time sim1 "
		  << iter -> totalWaitSM1
		  << " elapsed time sim2 "
		  << iter -> totalWaitSM2 << endl << endl;
	    
	    orderCounter++;

	iter = iter -> next;
	      }
    cout << "sim1 min elapsed time " << S1min << endl;
    cout << "sim1 max elapsed time " << S1max << endl;
    cout << "mean elapsed time " << S1total / orderCounter << endl;
    cout << orderCounter << " orders processed" << endl << endl;

    cout << "sim2 min elapsed time " << S2min << endl;
    cout << "sim2 max elapsed time " << S2max << endl;
    cout << "sim 2 mean elapsed time for all cusomers " << S2total/orderCounter
	 << endl;
   cout  << "sim2 mean elapsed time for supreme customers "
	 << S2totalSupreme/orderCounter << endl;
    cout << "sim2 mean elapsed time for regular customers "
	   << S2totalRegular/orderCounter << endl;
    cout << orderCounter << " orders processed" << endl;
    

}
// Effects: Keeps track of how long an Order has been in retrieval. Updates
// time. Initializes the time at which orders get to the packaging queue
// Returns: A bool that will tell the manager class to take the item off the 
// retrieval queue and put it in the packaging queue.
bool Retriever::isFetched()
{
    if( !isEmpty()){

	time++;
     
	
	(head -> timeFetched)--; // Marks passage of a unit of time at retrieval

	if (head -> timeFetched <= 0){ // if article has been fetched
	    head -> arrivalPackaging = time; // will be sent at this time
	    return true;
	    }
	else
	    return false;
    }
    else{
	time++;
	isWorking = false; // list is empty, retriever's job is done
	return false;
    }
   
}

// Effect: It fills the Queue with Orders whose specifications will be 
// initialized through cin.
void Retriever::fillQueue()
{
    Order toAdd;
    string status;
    string junk;
    
    while (cin >> junk){
        cin >> toAdd.ID >> junk >> status;

	if (status == "supreme")
	    toAdd.isSupreme = true;
	else
	    toAdd.isSupreme = false;

	cin >> junk >> junk  >> junk >> junk
	    >> toAdd.arrivalTime >> junk >> junk
	    >> toAdd.fetchTime >> junk >> junk
	    >> junk >> toAdd.packTime >> junk;

	toAdd.timeFetched = toAdd.fetchTime; // not started fetching yet
	toAdd.timePacked = toAdd.packTime;
	toAdd.totalWaitSM1 = 0;
	toAdd.totalWaitSM2 = 0;

	add(toAdd);
    }
}

void Retriever::copyOrdersFromList(Retriever toCopy)
{
    Order* iter = toCopy.head;

    while (iter != NULL){
	add(*iter);
	iter = iter -> next;
    }
}

Order* Retriever:: getHead()
{
    return head;
}

	
