#pragma once

#include "Component.h"
#include "GameLogic.h"
#include "GraphicMain.h"

class LogicComponent : public Component
{
private:
	GameLogic gl;
	GraphicMain* gm;
	GameObject* tempBoat;
	int tempBoatLength;
	bool tempBoatSpawned = false;
	Boat tempBoatB = Boat(1, {0,0});
	coordinate tempBoatCoords = { 0,0 };
	double counter = 0;

	bool tempPinSpawned = false;
	coordinate tempPinCoords = { 0,0 };
	GameObject* tempPin;

public:
	LogicComponent(GraphicMain* graphicmain);
	~LogicComponent();
	virtual void update(float elapsedTime);

	void stateNotStarted();
	void statePlacement();
	void statePlayerTurn();
	void stateAITurn();
	void stateGameOver();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

