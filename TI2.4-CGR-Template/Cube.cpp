#include "Cube.h"

Cube::Cube(float radius, glm::vec4 color)
{
	this->radius = radius * 0.5f;
	this->color = color;
}

void Cube::draw()
{
	tigl::begin(GL_QUADS);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColor(true);
	
	//Front
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, radius), color));
	//Right
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, radius), color));
	//Top
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, -radius), color));
	//Rear
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, -radius), color));
	//Left
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, radius, radius), color));
	//Bottom
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(radius, -radius, -radius), color));
	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-radius, -radius, -radius), color));

	tigl::end();
}