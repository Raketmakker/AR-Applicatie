#ifndef _BOAT_H_
#define _BOAT_H_

#include <iostream>
#include <vector>
#include "Struct.h"

using namespace std;

class Boat {
private:
    vector<coordinate> boat;
    int size = 0;
public:
    Boat(int boatSize, vector<coordinate> coords);
    Boat(int boatSize, coordinate coords);
    vector<coordinate> Boat_getBoat();
    void printCoords();
    bool operator==(const Boat& rhs);
};

#endif _BOAT_H_