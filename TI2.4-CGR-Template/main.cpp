#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "blobdetectionavans.h"
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace cv;
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GLFWwindow* visionWindow;

void init();
void update();
void draw();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    visionWindow = glfwCreateWindow(1400, 800, "Vision window", NULL, NULL);
    graphicsWindow = glfwCreateWindow(1400, 800, "Graphics window", NULL, NULL);
    
    glfwMakeContextCurrent(graphicsWindow);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(graphicsWindow))
	{
		update();
		draw();
		glfwSwapBuffers(graphicsWindow);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}


void init()
{
    glfwSetKeyCallback(graphicsWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

}


void update()
{

}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    tigl::begin(GL_TRIANGLES);
    tigl::addVertex(Vertex::PC(glm::vec3(-1, 0, 0), glm::vec4(1, 0, 0, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(0, 1, 0), glm::vec4(0, 0, 1, 1)));
    tigl::end();
}