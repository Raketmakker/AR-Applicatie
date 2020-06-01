#pragma once
#include "Component.h"
#include "GameObject.h";
#include <GLFW/glfw3.h>
#include <iostream>

class PositionTool : public Component
{
private:
	float rotation = 0;
	float speed;
	GLFWwindow* window;
public:
	void update(float deltaTime);
	void move(float angle, float fac);
	void rotate(float amount);
	PositionTool(GLFWwindow* window, float speed);
};

