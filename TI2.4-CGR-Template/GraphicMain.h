#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <list>
#include "GameObject.h"
#include "FpsCam.h"
#include "Line.h"

class GraphicMain
{
private:
	GLFWwindow* window;
	std::list<GameObject*> gameObjects;
	FpsCam* cam;

	const int gridSize = 10;
	const float tileSize = 20.0f;
	void drawGrid();
public:
	void init();
	void update(float deltaTime);
	void draw();
	void placeBoat(int x, int y);
	GraphicMain(GLFWwindow* window);
};

