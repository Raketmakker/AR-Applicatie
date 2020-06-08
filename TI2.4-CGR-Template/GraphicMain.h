#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <list>
#include "GameObject.h"
#include "FpsCam.h"
#include "Line.h"
#include "GraphicModel.h"
#include <iostream>
#include "Cube.h"
#include "Text.h"

class GraphicMain
{
private:
	
	std::list<GameObject*> gameObjects;
	FpsCam* cam;

	const int gridSize = 10;
	const float tileSize = 20.0f;
	const float gridHeight = -95;
	const float pinSize = 0.7f;
	const glm::vec3 shipOffset = glm::vec3(0, -100, 0);
	void drawGrid(int offsetX, int offsetZ);
public:
	GLFWwindow* window;
	Text* text;
	void init();
	void update(float deltaTime);
	void draw();
	void test();
	GameObject* firePin(int x, int z, int offsetX, int offsetZ);
	void setPinPosition(GameObject* pin, int x, int z, int offsetX, int offsetZ);
	void setPinHit(GameObject* pin, bool hit);
	GameObject* placeBoat(int x, int z, int length);
	void setBoatPosition(GameObject* ship, int x, int z, int length);
	GraphicMain(GLFWwindow* window);
};

