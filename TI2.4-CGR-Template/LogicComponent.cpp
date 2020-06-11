#include "LogicComponent.h"
#include <stdio.h>

LogicComponent::LogicComponent(GraphicMain* graphicmain, VisionModule* visionmodule)
{
	gm = graphicmain;
	gl = GameLogic(graphicmain);
	srand(time(NULL));

	vm = visionmodule;
}


LogicComponent::~LogicComponent()
{
}

Point2d selection;
coordinate sC;
void LogicComponent::update(float elapsedTime) {

	selection = vm->GetSelectionPos();
	sC = { (int)selection.x,(int)selection.y };
	//cout << "Logic: " << selection.x << ":" << selection.y << endl;

	switch (gl.gamestate) {
	case (GameState::STATE_NOT_STARTED):
		stateNotStarted();
		break;
	case (GameState::STATE_PLACEMENT):
		statePlacement();

		break;
	case (GameState::STATE_PLAYERTURN):
		statePlayerTurn();
		break;
	case (GameState::STATE_AITURN):
		stateAITurn();
		break;
	case (GameState::STATE_GAMEOVER):
		stateGameOver();
		break;
	}
	//gl.update(elapsedTime);
}

void LogicComponent::stateNotStarted()
{
	gm->text->setText({"Welcome to Battleships.",
					   "Use 'WASD' to move around.",
					   "Use 'SPACE' and 'SHIFT' to go up and down",
					   "Use your mouse to look around",
					   "Press 'Enter' to continue."});
	if (Input::getInstance().isPressed(GLFW_KEY_ENTER)) {
		gl.gamestate = GameState::STATE_PLACEMENT;
	}
}
void LogicComponent::statePlacement()
{
	//Changed coords

	tempBoatCoords.x = selection.x;
	tempBoatCoords.y = selection.y;
	tempBoatB = Boat(tempBoatLength, tempBoatCoords);
		

	gm->text->setText({ "Place a red marker on the real playboard to place a ship.",
						"If the ship is on the right spot, press ENTER to place the next ship.",
						"If you have placed 5 ships, press ENTER to start the game." });

	if (tempBoatSpawned) {
		//Callback coordinates
		//Check if boat overlaps

		gm->setBoatPosition(tempBoat, tempBoatCoords.x, tempBoatCoords.y, tempBoatLength);

		//Confirm location
		if (Input::getInstance().isPressed(GLFW_KEY_ENTER)) {

			if (!gl.getBordSpeler()->checkIfBoatOverlap(tempBoatB) && gl.getBordSpeler()->checkIfBoatIsInBounds(tempBoatB)) {
				gl.getBordSpeler()->addBoat(tempBoatB);
				tempBoatSpawned = false;
				cout << tempBoatCoords.x << ":" << tempBoatCoords.y << endl;
			}
			else 
			{
				cout << tempBoatCoords.x << ":" << tempBoatCoords.y << endl;
				gm->text->setText({ "Place a red marker on the real playboard to place a ship.",
						"If the ship is on the right spot, press ENTER to place the next ship.",
						"If you have placed 5 ships, press ENTER to start the game.",
						"Your ship is overlapping another ship or out of bounds, try placing it elsewhere."});
			}
		}
	}
	else
	{
		if (!gl.boats.empty()) {
			tempBoatLength = gl.boats.back();
			tempBoat = gm->placeBoat(0, 0, tempBoatLength);
			tempBoatB = Boat(tempBoatLength, { 0,0 });
			gl.boats.pop_back();
			tempBoatSpawned = true;
		}
		else
		{
			//Next state
			tempPin = gm->firePin(0, 0, 1, 0);

			gm->text->setText({ "This is the Players turn.",
						"Use your pionnetje to place your shot on the battlefield.",
						"Press 'Enter' to fire and place your shot.",
						"If your shot hits, it will become red, otherwise it will become blue." });
			AIBordGeneration();
			gl.gamestate = GameState::STATE_PLAYERTURN;
		}
	}
}
void LogicComponent::statePlayerTurn()
{
	//Changed coords

	tempPinCoords.x = selection.x;
	tempPinCoords.y = selection.y;

	gm->setPinPosition(tempPin, tempPinCoords.x, tempPinCoords.y, 1, 0);
	
	if (Input::getInstance().isPressed(GLFW_KEY_ENTER)) {
		cout << "BORDAI" << endl;
		gl.getBordAI()->printBord();
		cout << "Bord Speler" << endl;
		gl.getBordSpeler()->printBord();
		if (gl.getBordAI()->checkIfGuessed(sC)) {
			//gm->text->setText({ "This spot has already been guessed." });
		}
		else 
		{
			if (gl.getBordAI()->shootBoat(sC)) {
					
				gm->setPinHit(tempPin, 1);
			}
			else 
			{
				gm->setPinHit(tempPin, 0);
			}

			if (gl.getBordAI()->checkIfBoatWasDestroyed()) {
				gm->text->setText({"Congrats, you destroyed a boat."});
			}
				
			gl.gamestate = GameState::STATE_AITURN;
		}

		//Check if the game is over, if yes, go to gameover state
		if (gl.checkIfGameIsOver()) {
			gl.gamestate = GameState::STATE_GAMEOVER;
		}
		else
		{
			tempPin = gm->firePin(0, 0, 0, 0);
		}
	}
}

int AIX, AIY;
bool done = true;
void LogicComponent::stateAITurn()
{
	bool looping = true;
	while (looping) {
		//Generate random coordinates
		AIX = rand() % 10;
		AIY = rand() % 10;

		if (!gl.getBordSpeler()->checkIfGuessed({ AIX,AIY })) {
			gm->setPinPosition(tempPin, AIX, AIY, 0, 0);
			if (gl.getBordSpeler()->shootBoat({ AIX,AIY })) {
				gm->setPinHit(tempPin, 1);
			}
			else 
			{
				gm->setPinHit(tempPin, 0);
			}
			looping = false;
		}
	}
	looping = true;

	if (gl.getBordAI()->checkIfBoatWasDestroyed()) {
		gm->text->setText({ "Yikes, the AI destroyed one of your boats." });
	}
	
	gl.gamestate = GameState::STATE_PLAYERTURN;
	//Check if the game is over, if yes, go to gameover state
	if (gl.checkIfGameIsOver()) {
		gl.gamestate = GameState::STATE_GAMEOVER;
	}
	else 
	{
		tempPin = gm->firePin(0, 0, 1, 0);
	}
}
void LogicComponent::stateGameOver()
{
	if (gl.getBordAI()->checkIfDead()) {
		gm->text->setText({ "You have won!",
							"Congratulations!" });
	}
	else 
	{
		gm->text->setText({ "The AI has won!",
							"You lost" });
	}
}

void LogicComponent::AIBordGeneration() {
	bool looping = true;
	while (!gl.boatsAI.empty()) {
		//Get last length and pop it out
		tempBoatLength = gl.boatsAI.back();
		gl.boatsAI.pop_back();

		while (looping) {
			//Generate random coordinates
			AIX = rand() % 10;
			AIY = rand() % 10;

			tempBoatB = Boat(tempBoatLength, { AIX,AIY });

			if (!gl.getBordAI()->checkIfBoatOverlap(tempBoatB) && gl.getBordAI()->checkIfBoatIsInBounds(tempBoatB)) {
				gl.getBordAI()->addBoat(tempBoatB);
				looping = false;
			}
		}
		looping = true;
		gl.getBordAI()->printBord();
	}
	gl.getBordAI()->printBord();
}