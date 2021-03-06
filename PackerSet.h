#ifndef PACKERSET_H
#define PACKERSET_H
#include "Packager.h"
const int numPackers = 3;

class PackerSet {

public:

    void addSupreme(Order toAdd);
    void addNormal(Order toAdd);

    bool isWorking();

    void Update();

//private:

    Packager packerSet[numPackers];
};
#endif
