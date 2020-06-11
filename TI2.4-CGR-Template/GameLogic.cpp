#include <iostream>
#include "GameLogic.h"
using namespace std;

GameLogic::GameLogic()
{
}

GameLogic::GameLogic(GraphicMain* graphicMain)
{
	gamestate = GameState::STATE_NOT_STARTED;
	gm = graphicMain;
}

GameLogic::~GameLogic()
{
}

void GameLogic::GameLogic_Init() {

}

Bord* GameLogic::getBordSpeler() {
    return &bordSpeler;
}

Bord* GameLogic::getBordAI() {
    return &bordAI;
}

void GameLogic::printBords() {
    cout << "Speler bord:" << endl;
    bordSpeler.printBord();
    cout << "AI bord:" << endl;
    bordAI.printBord();
}

bool GameLogic::checkIfGameIsOver()
{
	return (bordAI.checkIfDead() || bordSpeler.checkIfDead());
}

void GameLogic::initBordAI() {
	vector<int> boats = { 5,4,3,3,2 };
	Boat tempBoat = Boat(1, { 0,0 });
	int tempBoatLength = 0;
	int x, y;
	while (!boats.empty()) {
		tempBoatLength = boats.back();
		boats.pop_back();
		while (1) {
			x = rand() % 10;
			y = rand() % 10;

			tempBoat = Boat(tempBoatLength, { x,y });
			if (!bordSpeler.checkIfBoatOverlap(tempBoat) && bordSpeler.checkIfBoatIsInBounds(tempBoat)) {
				bordSpeler.addBoat(tempBoat);
			}
		}
	}
}

void GameLogic::update(float elapsedTime) {
	
};