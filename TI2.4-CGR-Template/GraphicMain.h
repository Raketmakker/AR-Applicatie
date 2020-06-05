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
	GLFWwindow* window;
	std::list<GameObject*> gameObjects;
	FpsCam* cam;
	Text* text;

	const int gridSize = 10;
	const float tileSize = 20.0f;
	const float gridHeight = -95;
	const float pinSize = 0.7f;
	const glm::vec3 shipOffset = glm::vec3(0, -100, 0);
	void drawGrid(int offsetX, int offsetZ);
public:
	void init();
	void update(float deltaTime);
	void draw();
	void firePin(int x, int z, int offsetX, int offsetZ, bool hit);
	void test();
	GameObject* placeBoat(int x, int z, int length);
	GraphicMain(GLFWwindow* window);
};

