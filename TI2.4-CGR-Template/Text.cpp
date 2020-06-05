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

//Draw the textfields
void Text::draw()
{	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLTtext* text1 = gltCreateText();
	gltSetText(text1, "Hello World!");
	gltBeginDraw();
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2D(text1, 0.0f, 0.0f, 1.0f);
	gltEndDraw();
	gltDeleteText(text1);

	glBindVertexArray(0);
	tigl::shader->use();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}