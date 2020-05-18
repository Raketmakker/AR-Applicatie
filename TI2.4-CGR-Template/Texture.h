#pragma once

#include <gl/glew.h>
#include <string>

class Texture
{
	GLuint id = -1;
public:
	Texture(const std::string& fileName);
	void bind();
};