#include "Text.h"

//Initialize the draw component
Text::Text()
{
	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		std::cout << "Could not initialize gltInit" << std::endl;
		exit(2);
	}
	tigl::shader->use();
}

Text::~Text()
{
	gltTerminate();
}

void Text::setSelected(int i)
{
	this->selected = i;
}

void Text::setText(std::vector<std::string> texts)
{
	this->texts.clear();
	this->texts = texts;
}

//Draw the textfields
void Text::draw()
{	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for (auto& txt : texts)
	{
		GLTtext* glt = gltCreateText();
		gltSetText(glt, txt.c_str());
		this->gltTexts.push_back(glt);
	}
	
	size_t length = gltTexts.size();
	gltBeginDraw();
	for (size_t i = 0; i < length; i++)
	{
		if (selected == i)
		{
			gltColor(1.0f, 0, 0, 1.0f);
		}
		else
		{
			gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		gltDrawText2D(gltTexts[i], borderOffset, borderOffset + i * textHight, 2.0f);
	}
	gltEndDraw();

	for (size_t i = 0; i < length; i++)
	{
		gltDeleteText(gltTexts[i]);
	}
	gltTexts.clear();
	glBindVertexArray(0);
	tigl::shader->use();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}