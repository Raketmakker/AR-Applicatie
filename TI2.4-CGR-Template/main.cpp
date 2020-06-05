#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_image.h"
#include "GraphicMain.h"
#include "VisionModule.h"
using namespace cv;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GraphicMain* graphicMain;

void init();
void update();
void draw();
void VisionCallback(int x, int y);

int main(void)
{
    VisionModule visionModule(VisionCallback);
    visionModule.Start();

    if (!glfwInit())
        throw "Could not initialize glwf";
    graphicsWindow = glfwCreateWindow(1400, 800, "Graphics window", NULL, NULL);
    
    glfwMakeContextCurrent(graphicsWindow);

    tigl::init();

    graphicMain = new GraphicMain(graphicsWindow);
    graphicMain->init();
    graphicMain->test();

	while (!glfwWindowShouldClose(graphicsWindow))
	{
        update();
		draw();
        glfwSwapBuffers(graphicsWindow);
		glfwPollEvents();
	}

	glfwTerminate();
    gltTerminate();
    visionModule.Stop();

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

void VisionCallback(int x, int y)
{
    cout << "Selection is on (" << x << "," << y << ")\n";
}