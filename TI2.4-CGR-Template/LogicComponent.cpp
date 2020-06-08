#include "LogicComponent.h"
#include <stdio.h>

LogicComponent::LogicComponent(GraphicMain* graphicmain)
{
	gm = graphicmain;
	gl.GameLogic_Init();
}

LogicComponent::~LogicComponent()
{
}

void LogicComponent::update(float elapsedTime) {
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
	if(glfwGetKey(gm->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		gl.gamestate = GameState::STATE_PLACEMENT;
	}
}
void LogicComponent::statePlacement()
{
	gm->text->setText({ "Place a red marker on the real playboard to place a ship.",
						"If the ship is on the right spot, press ENTER to place the next ship.",
						"If you have placed 5 ships, press ENTER to start the game." });

	if (tempBoatSpawned) {
		//Callback coordinates
		//Check if boat overlaps



		//Confirm location
		if (glfwGetKey(gm->window, GLFW_KEY_ENTER) == GLFW_PRESS) {

			/*if (gl.getBordAI()->addBoat();*/
			tempBoatSpawned = false;
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
			gl.gamestate = GameState::STATE_PLAYERTURN;
		}
	}
}
void LogicComponent::statePlayerTurn()
{
	gm->text->setText({ "This is the Player turn." });
}
void LogicComponent::stateAITurn()
{
}
void LogicComponent::stateGameOver()
{
}
;