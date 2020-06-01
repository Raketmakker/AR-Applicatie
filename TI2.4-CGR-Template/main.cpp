#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "blobdetectionavans.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GraphicMain.h"
using namespace cv;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GLFWwindow* visionWindow;
GraphicMain* graphicMain;

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

    graphicMain = new GraphicMain(graphicsWindow);
    graphicMain->init();

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
    
}

void update()
{
    float time = glfwGetTime();
    static float lastTime;
    float deltaTime = time - lastTime;
    lastTime = time;
    graphicMain->update(deltaTime);
}

void draw()
{
    graphicMain->draw();
}