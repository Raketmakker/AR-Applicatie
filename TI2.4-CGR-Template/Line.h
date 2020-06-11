#pragma once
#include "GameObject.h"
#include "DrawComponent.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Line : public DrawComponent
{
private:
	std::vector<glm::vec3> verts;
	glm::vec4 color;
public:
	Line(glm::vec3 start, glm::vec3 end, glm::vec4 color, float width);
	void draw();
};

