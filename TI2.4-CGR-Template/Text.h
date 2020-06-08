#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#define GLT_IMPLEMENTATION
#include "gltext.h"
#include <iostream>
#include "DrawComponent.h"
#include <vector>

class Text : public DrawComponent
{
private:
	const int textHight = 40;
	const int borderOffset = 10;
	int selected = -1;
	std::vector<std::string> texts;
	std::vector<GLTtext*> gltTexts;
public:
	Text();
	~Text();
	void setSelected(int i);
	void setText(std::vector<std::string> texts);
	virtual void draw() override;
};