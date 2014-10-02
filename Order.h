#ifndef ORDER_H
#define ORDER_H

struct Order{
    int ID;
    int fetchTime; // how long it takes to fetch
    int packTime;
    int timeFetched; // the time its spent at the retrieval unit
    int timePacked;
    int arrivalTime;
    int totalWaitSM1;
    int totalWaitSM2;
    int arrivalPackaging;
    bool isSupreme;
    Order* next;
};
#endif

