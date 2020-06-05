#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#define GLT_IMPLEMENTATION
#include "gltext.h"
#include <iostream>

class Text
{
private:
	GLTtext* text;
	GLFWwindow* window;
public:
	Text(GLFWwindow* window);
	~Text();
	void draw(glm::mat4 mpv);
};