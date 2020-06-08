#include "Line.h"

Line::Line(glm::vec3 start, glm::vec3 end, glm::vec4 color, float width)
{
	width /= 2;
	float angle = glm::degrees(atan((end.z - start.z) / (end.x - start.x)));
	angle += 90.0f;

	float x = width * cos(glm::radians(angle));
	float z = width * sin(glm::radians(angle));
	verts.push_back(start + glm::vec3(x, 0, z));
	verts.push_back(end + glm::vec3(x, 0, z));
	angle += 180;

	x = width * cos(glm::radians(angle));
	z = width * sin(glm::radians(angle));

	verts.push_back(end + glm::vec3(x, 0, z));
	verts.push_back(start + glm::vec3(x, 0, z));

	this->color = color;
}

void Line::draw()
{
	tigl::begin(GL_QUADS);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColor(true);
	
	for (auto& vert : this->verts)
	{
		tigl::addVertex(tigl::Vertex::PC(vert, color));
	}
	tigl::end();
}