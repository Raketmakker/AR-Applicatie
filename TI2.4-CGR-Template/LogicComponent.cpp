#include "LogicComponent.h"
#include <stdio.h>

LogicComponent::LogicComponent(GraphicMain* graphicmain)
{
	gm = graphicmain;
	gl = GameLogic(graphicmain);
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
	if (glfwGetKey(gm->window, GLFW_KEY_UP) == GLFW_PRESS) {
		counter++;
		tempBoatCoords.x = (counter /100);
		tempBoatCoords.y = (counter / 100);
		if (counter > 1000) counter -= 1000;
		cout << tempBoatCoords.x << ":" << tempBoatCoords.y << endl;
		tempBoatB = Boat(tempBoatLength, tempBoatCoords);
	}
		

	gm->text->setText({ "Place a red marker on the real playboard to place a ship.",
						"If the ship is on the right spot, press ENTER to place the next ship.",
						"If you have placed 5 ships, press ENTER to start the game." });

	if (tempBoatSpawned) {
		//Callback coordinates
		//Check if boat overlaps

		gm->setBoatPosition(tempBoat, tempBoatCoords.x, tempBoatCoords.y, tempBoatLength);



		//Confirm location
		if (glfwGetKey(gm->window, GLFW_KEY_ENTER) == GLFW_PRESS) {

			if (!gl.getBordAI()->checkIfBoatOverlap(tempBoatB) && gl.getBordAI()->checkIfBoatIsInBounds(tempBoatB)) {
				gl.getBordAI()->addBoat(tempBoatB);
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
			gl.gamestate = GameState::STATE_PLAYERTURN;
		}
	}
}
void LogicComponent::statePlayerTurn()
{
	if (glfwGetKey(gm->window, GLFW_KEY_UP) == GLFW_PRESS) {
		counter++;
		tempPinCoords.x = (counter / 100);
		tempPinCoords.y = (counter / 100);
		if (counter > 1000) counter -= 1000;
		cout << tempPinCoords.x << ":" << tempPinCoords.y << endl;
		gm->setPinPosition(tempPin, tempPinCoords.x, tempPinCoords.y, 1, 0);
	}

	gm->text->setText({ "This is the Players turn.",
						"Use your pionnetje to place your shot on the battlefield.",
						"Press 'Enter' to fire and place your shot.",
						"If your shot hits, it will become red, otherwise it will become blue."});
	
	if (tempPinSpawned) {
		if (glfwGetKey(gm->window, GLFW_KEY_ENTER) == GLFW_PRESS) {

		}

	}
}
void LogicComponent::stateAITurn()
{
}
void LogicComponent::stateGameOver()
{
}

void LogicComponent::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		tempBoatCoords.y++;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		tempBoatCoords.y--;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		tempBoatCoords.x++;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		tempBoatCoords.x--;

	tempBoatB = Boat(tempBoatLength, tempBoatCoords);
	cout << tempBoatCoords.x << ":" << tempBoatCoords.y << endl;
}