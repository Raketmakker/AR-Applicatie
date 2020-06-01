#pragma once
#include "DrawComponent.h"
#include "GameObject.h"
#include "tigl.h"
#include <iostream>

class Cube : public DrawComponent
{
private:
	float radius;
	glm::vec4 color;
public:
	Cube(float size, glm::vec4 color);
	void draw();
};

