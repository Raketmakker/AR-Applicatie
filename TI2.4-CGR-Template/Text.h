#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#define GLT_IMPLEMENTATION
#include "gltext.h"
#include <iostream>
#include "DrawComponent.h"

class Text : public DrawComponent
{
public:
	Text();
	~Text();
	virtual void draw() override;
};