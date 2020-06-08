#include "boat.h"
#include "Struct.h"
using namespace std;

Boat::Boat(int boatSize, vector<coordinate> coords) {
    size = boatSize;
    for (coordinate coord : coords) {
        boat.push_back(coord);
    }
}

Boat::Boat(int boatSize, coordinate coords) {
    size = boatSize;
    boat.push_back(coords);
    for (int i = 1; i < boatSize; i++) {
        coords.x++;
        boat.push_back(coords);
    }
}

vector<coordinate> Boat::Boat_getBoat() {
    return boat;
}

void Boat::printCoords() {
    cout << "Boot:" << endl;
    for (coordinate c : boat) {
        cout << c.x << ":" << c.y << endl;
    }
}

bool Boat::operator ==(const Boat& rhs) {
    Boat right = rhs;
    if (right.boat.size() == boat.size()) {
        for (int i = 0; i < boat.size(); i++) {
            if (!(right.boat[i] == boat[i])) {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
};
