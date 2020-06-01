#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <list>
#include "GameObject.h"
#include "FpsCam.h"
#include "Line.h"
#include "GraphicModel.h"
#include <iostream>

class GraphicMain
{
private:
	GLFWwindow* window;
	std::list<GameObject*> gameObjects;
	FpsCam* cam;

	const int gridSize = 10;
	const float tileSize = 20.0f;
	const float gridHeight = -95;
	const glm::vec3 shipOffset = glm::vec3(0, -100, 0);
	void drawGrid();
public:
	void init();
	void update(float deltaTime);
	void draw();
	void placeBoat(int x, int y, int length);
	GraphicMain(GLFWwindow* window);
};

