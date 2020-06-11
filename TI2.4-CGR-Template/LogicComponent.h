#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Component.h"
#include "GameLogic.h"
#include "GraphicMain.h"
#include "VisionModule.h"
#include <opencv2/opencv.hpp>

class LogicComponent : public Component
{
private:
	GameLogic gl;
	GraphicMain* gm;
	VisionModule* vm;

	GameObject* tempBoat;
	int tempBoatLength;
	bool tempBoatSpawned = false;
	Boat tempBoatB = Boat(1, {0,0});
	coordinate tempBoatCoords = { 0,0 };
	double counter = 0;
	int AIX, AIY;

	coordinate tempPinCoords = { 0,0 };
	GameObject* tempPin;

public:
	LogicComponent(GraphicMain* graphicmain, VisionModule* visionmodule);
	~LogicComponent();
	virtual void update(float elapsedTime);

	void stateNotStarted();
	void statePlacement();
	void statePlayerTurn();
	void stateAITurn();
	void stateGameOver();

	void AIBordGeneration();
};

