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
	Boat tempBoatB;
public:
	LogicComponent(GraphicMain* graphicmain);
	~LogicComponent();
	virtual void update(float elapsedTime);

	void stateNotStarted();
	void statePlacement();
	void statePlayerTurn();
	void stateAITurn();
	void stateGameOver();

};

