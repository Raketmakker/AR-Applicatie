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
#include <thread>
#include "GameLogic.h"
#include "LogicComponent.h"
#include "Input.h"

using namespace cv;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GraphicMain* graphicMain;
GameObject* logicObject;

void init();
void update();
void draw();

int main(void)
{
    VisionModule visionModule;
    visionModule.Start();

    if (!glfwInit())
        throw "Could not initialize glwf";
    graphicsWindow = glfwCreateWindow(1400, 800, "Graphics window", NULL, NULL);

    glfwMakeContextCurrent(graphicsWindow);

    tigl::init();

    graphicMain = new GraphicMain(graphicsWindow);
    graphicMain->init();
    //graphicMain->test();

	logicObject = new GameObject();
	logicObject->addComponent(new LogicComponent(graphicMain,&visionModule));

	Input::getInstance().init(graphicsWindow);

	while (!glfwWindowShouldClose(graphicsWindow))
	{
		Input::getInstance().update();
        update();
		draw();
        glfwSwapBuffers(graphicsWindow);
		glfwPollEvents();
	}

	visionModule.Stop();
	glfwTerminate();
    gltTerminate();

	while (!visionModule.IsThreadDone()) {
		this_thread::sleep_for(1ms);
	}

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
	logicObject->update(deltaTime);
}

void draw()
{
    graphicMain->draw();
}

void VisionCallback(int x, int y)
{
    cout << "Selection is on (" << x << "," << y << ")\n";
}