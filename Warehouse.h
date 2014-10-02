#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "retriever.h"
#include "Packager.h"

const int numPackers = 3;

class Warehouse {

public:
    
    void sendToPackaging(); // considers supremes
    void sendToPackagingNormal(); // doesn't consider supremes
    void startSimulation();

    void addSupreme(Order toAdd);
    void addNormal(Order toAdd);
    bool packagerisWorking();

    void shipOrderSM1(int i);
    void shipOrderSM2(int i);
    
private:
    
    Retriever retriever, retrieverS2;
    Retriever buffer; 
    Packager packerSet[numPackers];
    int time;
};
#endif

