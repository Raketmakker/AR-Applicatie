#ifndef _BORD_H_
#define _BORD_H_
#include <iostream>
#include "boat.h"
#include "struct.h"

using namespace std;
class Bord {

private:
    int bord[10][10] = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0} };
    vector<Boat> boats;
    vector<Boat> Ripboats;
    vector<coordinate> guesses;

public:
    void addBoat(Boat boat);

    void printBoats();

    void fillBord();

    bool shootBoat(coordinate c);

    bool findBoat(coordinate c);

    void printBord();

    bool checkIfBoatOverlap(Boat boat);

    bool checkIfGuessed(coordinate c);

    bool checkIfBoatWasDestroyed();

    int checkIfDead();
};

#endif _BORD_H_
