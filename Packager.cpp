#include "Packager.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Packager::Packager()
{
    head = NULL;
    tail = NULL;
    time = 0; // current time
    isWorking = true;
    normalWait = 0;
    supremeWait = 0;
    
}


void Packager::addNormal(Order toAdd)
{
    Order* newOrder = new Order;

    *newOrder = toAdd;
    
    normalWait += toAdd.packTime;

    if (isEmpty()){
	head = newOrder;
	tail = head;
    }

    tail -> next = newOrder;
    tail = newOrder;
    
    newOrder -> next = NULL;

    
}

void Packager::addSupreme(Order toAdd)
{
    Order* newOrder = new Order;

    *newOrder = toAdd;

    supremeWait += toAdd.packTime;
    normalWait += toAdd.packTime;
 
    if (isEmpty()){
	newOrder -> next = head;
	head  = newOrder;
	tail = head;
    }
    else if (!head -> isSupreme){ // if no other supremes in queue
	newOrder -> next = head;
	head = newOrder;
    }


    else {

	Order* curr  = head; //to find where in the queue toAdd should go
	Order* prev = NULL;
	while(curr != NULL && curr -> isSupreme){ //find last supreme in queue
	    prev  = curr;
	    curr = curr -> next;
	}
 
	newOrder -> next = curr;
	prev -> next = newOrder;
    }
   
}

bool Packager::isEmpty()
{
    return head == NULL;
}

void Packager::print()
{
    Order* iter = head;
    if (iter == NULL)
	cout << "empty list" << endl;

    while (iter != NULL){
	cout << "Order " << iter -> ID << " for ";

	   if (iter -> isSupreme)
		cout << "supreme customer ";
	    else
		cout << "regular customer ";
	    
	    cout  << "arrived at time " << iter -> arrivalTime
		  << endl << "fetch time " << iter -> fetchTime
		  << " minutes, pack time " << iter -> packTime
		  << endl
		  << "the order was added to packaging queue at time "
		  << iter -> arrivalPackaging << endl << endl;
	    

	iter = iter -> next;}
	      
}

bool Packager::isPacked()
{
    time++;
    if( !isEmpty()){
	//cout << time << endl;

	isWorking = true;
    
	
	(head -> timePacked)--; // Marks passage of a unit of time at retrieval
	
	if (head -> timePacked <= 0){ // if article has been packed
	    return true;
	    }
	else
	    return false;
    }
    else{
	
	isWorking = false; // list is empty, packers job is done
	return false;
    }
}

Order Packager::remove()
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

int Packager::getnormalWait()
{
    return normalWait;
}

int Packager::getsupremeWait()
{
    return supremeWait;
}
