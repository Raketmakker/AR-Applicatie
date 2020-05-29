#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "blobdetectionavans.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h";
#include "FpsCam.h"
#include "GameObject.h"
#include "GraphicModel.h"
using namespace cv;
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* graphicsWindow;
GLFWwindow* visionWindow;
std::list<GameObject*> gameObjects;
FpsCam* cam;

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
    glEnable(GL_DEPTH_TEST);
    cam = new FpsCam(graphicsWindow);

    GameObject* ship = new GameObject();
    ship->position = glm::vec3(0, -100, 0);
    ship->addComponent(new GraphicModel("models/Ship2/Ship2.obj"));
    gameObjects.push_back(ship);
}

void update()
{
    cam->update(graphicsWindow);
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(100.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(cam->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableTexture(true);

    for (auto& o : gameObjects)
        o->draw();
}