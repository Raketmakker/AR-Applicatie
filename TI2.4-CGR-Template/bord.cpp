#include <iostream>
#include <algorithm>
#include "bord.h"

using namespace std;

bool Bord::addBoat(Boat boat) {
    bool overlap = false;
    for (coordinate c : boat.Boat_getBoat()) {
        if (findBoat(c)) overlap = true;
    }

    if (!overlap) {
        boats.push_back(boat);
        fillBord();
        return true;
    }
    return false;
}

void Bord::printBoats() {
    for (Boat boat : boats) {
        boat.printCoords();
    }
}

void Bord::fillBord() {

    for (Boat boat : boats) {
        for (coordinate c : boat.Boat_getBoat()) {
            bord[c.x][c.y] = 1;
        }
    }
}

bool Bord::shootBoat(coordinate c) {

    if (checkIfGuessed(c)) {
        return false;
    }
    else {
        cout << "Good guess" << endl;
    }

    guesses.push_back(c);
    if (findBoat(c)) {
        bord[c.x][c.y] = -2;
        if (checkIfBoatWasDestroyed()) {
            cout << "You destroyed a boat!" << endl;
        }
        return true;
    }
    else {
        bord[c.x][c.y] = 2;
        return false;
    }
    

};

bool Bord::findBoat(coordinate c) {
    return (bord[c.x][c.y] == 1);
}

bool Bord::checkIfGuessed(coordinate c) {
    return(find(guesses.begin(), guesses.end(), c) != guesses.end());
}

bool Bord::checkIfBoatWasDestroyed() {
    int counter = 0;
    for (Boat b : boats) {
        counter = b.Boat_getBoat().size();
        for (coordinate c : b.Boat_getBoat()) {
            if (bord[c.x][c.y] == -2) counter--;
        }
        if (counter == 0) {
            boats.erase(remove(boats.begin(), boats.end(), b), boats.end());
            Ripboats.push_back(b);
            return true;
        }
    }
    return false;
}

int Bord::checkIfDead() {
    int* currentElement = &(bord[0][0]); // Create pointer to first element

    for (int i = 0; i < 10 * 10; i++)
    {
        if (*currentElement == 1)
        {
            return false;
        }
        currentElement++;
    }
    return true;
}
    
void Bord::printBord() {
    cout << "--------------------" << endl;
    for (int i = 0; i < 10; i++) {
        for (auto& column : bord) {
            cout << (int)column[i] << " ";
        }
        cout << endl;
    }
    
    cout << "--------------------" << endl;
}
