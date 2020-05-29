#pragma once
#include "DrawComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "tigl.h";

class Pane : public DrawComponent
{
private:
	float scale;
	bool grounded;
	Texture* texture;
public:
	void draw();
	Pane(float scale, std::string fileName, bool grounded);
};

