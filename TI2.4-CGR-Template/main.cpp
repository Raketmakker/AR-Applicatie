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
void game();

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

	/*GameObject* pin = graphicMain->firePin(0, 0, 0, 0);
	GameObject* pin2 = graphicMain->firePin(1, 1, 1, 0);
	graphicMain->setPinHit(pin, 1);
	graphicMain->setPinHit(pin2, 0);*/

	logicObject = new GameObject();
	logicObject->addComponent(new LogicComponent(graphicMain));

    //std::thread first(game);

	while (!glfwWindowShouldClose(graphicsWindow))
	{
        update();
		draw();
        glfwSwapBuffers(graphicsWindow);
		glfwPollEvents();
	}
	visionModule.Stop();
	glfwTerminate();
    gltTerminate();

    return 0;
}

GameLogic gl;

void game() {
	Boat boat0 = Boat(3, { {8,7},{8,8},{8,9} });
	Boat boat1 = Boat(3, { {0,0},{0,1},{0,2} });
	Boat boat2 = Boat(4, { {5,4},{5,5},{5,6},{5,7} });
	Boat boat3 = Boat(5, { {9,0},{9,1},{9,2},{9,3} });

	Bord* speler = gl.getBordSpeler();
	speler->addBoat(boat0);
	speler->addBoat(boat1);
	speler->addBoat(boat2);
	speler->addBoat(boat3);

	Bord* AI = gl.getBordAI();
	AI->addBoat(boat0);
	AI->addBoat(boat1);
	AI->addBoat(boat2);
	AI->addBoat(boat3);

	int spelerX, spelerY, AIX, AIY;
	while (!(speler->checkIfDead()) && !(AI->checkIfDead())) {
		gl.printBords();

		//Player's turn
		cout << "Player's turn" << endl;
		while (1) {
			if (!(AI->checkIfGuessed({ spelerX, spelerY }))) {
				break;
			}
			cout << "This has already been guessed." << endl << "Try again" << endl;
		}

		AI->shootBoat({ spelerX, spelerY });

		//AI turn
		cout << "AI's turn" << endl;
		while (1) {
			AIX = rand() % 10;
			AIY = rand() % 10;
			if (!(speler->checkIfGuessed({ AIX, AIY }))) {
				break;
			}
		}

		speler->shootBoat({ AIX, AIY });

	}
	gl.printBords();

	if (!(speler->checkIfDead())) {
		cout << "Speler won!" << endl;
	}
	else
	{
		cout << "AI won!" << endl;
	}
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