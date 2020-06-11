#include "Pane.h"
#include "stb_image.h"

Pane::Pane(float scale, std::string fileName, bool grounded)
{
	this->scale = scale / 2;
	this->texture = new Texture(fileName);
	this->grounded = grounded;
}

void Pane::draw()
{
	tigl::shader->enableTexture(true);
	tigl::shader->enableColor(false);
	this->texture->bind();
	tigl::begin(GL_QUADS);
	if (grounded)
	{
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(-scale, 0, -scale), glm::vec2(0, 0)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(scale, 0, -scale), glm::vec2(0, 1)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(scale, 0, scale), glm::vec2(1, 1)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(-scale, 0, scale), glm::vec2(1, 0)));
	}
	else
	{
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(-scale, -scale, 0), glm::vec2(0, 0)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(scale, -scale, 0), glm::vec2(0, 1)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(scale, scale, 0), glm::vec2(1, 1)));
		tigl::addVertex(tigl::Vertex::PT(glm::vec3(-scale, scale, 0), glm::vec2(1, 0)));
	}
	tigl::end();
}