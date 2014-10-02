#include "PackerSet.h"
using namespace std;
#include <cstdlib>
#include <iostream>

void PackerSet::addSupreme(Order toAdd)
{
    int shortest = 0; // keep track of index of queue with shortest wait

    for(int i = 0; i < numPackers; i++){
	if (packerSet[i].supremeWait < packerSet[shortest].supremeWait)
	    shortest = i;
    }
    packerSet[shortest].addSupreme(toAdd);
}

void PackerSet::addNormal(Order toAdd)
{
    int shortest = 0;
    for (int i =0; i < numPackers; i++){
	if(packerSet[i].normalWait < packerSet[shortest].normalWait)
	    shortest = i;
    }
    packerSet[shortest].addNormal(toAdd);
}

bool PackerSet::isWorking()
{
    bool isWorking = false;

    for (int i = 0; i < numPackers; i++){
	if (packerSet[i].isWorking)
	    isWorking = true;
    }
    return isWorking;
}

void PackerSet::Update()
{
    for(int i = 0; i < numPackers; i++)
	packerSet[i].isPacked();
}
