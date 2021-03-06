#include "Warehouse.h"
#include <iostream>
using namespace std;

void Warehouse::sendToPackaging()
{
    // the order removed from the retriever queue will be added to a packager
    Order toSend = (retriever.remove());
    
    if (toSend.isSupreme){
	addSupreme(toSend);
    }

    if (!toSend.isSupreme){
	addNormal(toSend);
    }
}

void Warehouse::startSimulation()
{
    // read original data into the Q called retriever
    retriever.fillQueue();
    // make a copy of it for second simulation
    retrieverS2.copyOrdersFromList(retriever);

    buffer.copyOrdersFromList(retriever);
    time = 0;
    
    // Simulation without considering supremes
    while (retrieverS2.isWorking || packagerisWorking()){
	time++;
	if ( retrieverS2.isFetched()){
	    sendToPackagingNormal();
	}

	for(int i = 0; i < numPackers; i++){
	    if(packerSet[i].isPacked()){
		shipOrderSM1(i);
	    }
	  
	}
    }

 

    time = 0;
    // Simulation considering Supremes
    while(retriever.isWorking || packagerisWorking()){
	time++;
	if(retriever.isFetched()){
      
	   sendToPackaging();
	}

	for (int i = 0; i < numPackers; i++){
	   
	    if (packerSet[i].isPacked()){
		shipOrderSM2(i);
	    }
     	
	}
    }


    buffer.print();
}


void Warehouse::shipOrderSM2(int i)
{
    
    Order temp = packerSet[i].remove();
    temp.totalWaitSM2 = time - temp.arrivalTime;

    if (temp.isSupreme)
	packerSet[i].supremeWait -= temp.packTime;
    else
	packerSet[i].normalWait -= temp.packTime;
    

    Order* iter = buffer.getHead();
    while (iter != NULL && temp.ID != iter -> ID)
	iter = iter -> next;
   
    if( iter != NULL) 
	iter -> totalWaitSM2 = temp.totalWaitSM2;
}

void Warehouse::shipOrderSM1(int i)
{
    Order temp = packerSet[i].remove();
    packerSet[i].normalWait -= temp.packTime;
    temp.totalWaitSM1 = time - temp.arrivalTime + 1;
    
    Order* iter = buffer.getHead();
    while (iter != NULL && temp.ID != iter -> ID)
	iter = iter -> next;
    
    if (iter != NULL)
	iter -> totalWaitSM1 = temp.totalWaitSM1;
    
}




void Warehouse::sendToPackagingNormal()
{
     Order toSend = (retrieverS2.remove());
     addNormal(toSend);
}
void Warehouse::addSupreme(Order toAdd)
{
    int shortest = 0; // keep track of index of queue with shortest wait

    for(int i = 0; i < numPackers; i++){
	if (packerSet[i].getsupremeWait()
	    <= packerSet[shortest].getsupremeWait())
	    shortest = i;
    }
    packerSet[shortest].addSupreme(toAdd);
}

void Warehouse::addNormal(Order toAdd)
{
    int shortest = 0;
    for (int i =0; i < numPackers; i++){
	if(packerSet[i].getnormalWait()
	   <= packerSet[shortest].getnormalWait())
	    shortest = i;
    }
    packerSet[shortest].addNormal(toAdd);
}

bool Warehouse::packagerisWorking()
{
    bool isWorking = false;

    for (int i = 0; i < numPackers; i++){
	if (packerSet[i].isWorking)
	    isWorking = true;
    }
    return isWorking;
}
