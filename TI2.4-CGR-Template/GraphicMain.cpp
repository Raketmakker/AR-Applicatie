#include "GraphicMain.h"

GraphicMain::GraphicMain(GLFWwindow* window)
{
	this->window = window;

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });
    glEnable(GL_DEPTH_TEST);
}

//The place to create gameobjects which last the entire game
void GraphicMain::init()
{
    this->cam = new FpsCam(window);
    drawGrid();
}

//Draws the grid where the boats in sail
void GraphicMain::drawGrid()
{
    GameObject* line;

    for (size_t x = 0; x <= gridSize; x++)
    {
        line = new GameObject();
        line->addComponent(new Line(glm::vec3(x * tileSize, gridHeight, 0), glm::vec3(x * tileSize, gridHeight, gridSize * tileSize), glm::vec4(0, 0, 0, 0), 3.0f));
        gameObjects.push_back(line);
    }

    for (size_t z = 0; z <= gridSize; z++)
    {
        line = new GameObject();
        line->addComponent(new Line(glm::vec3(0, gridHeight, z * tileSize), glm::vec3(gridSize * tileSize, gridHeight, z * tileSize), glm::vec4(0, 0, 0, 0), 3.0f));
        gameObjects.push_back(line);
    }
}

//Updates all the gameObjects by deltaTime (frame interval)
void GraphicMain::update(float deltaTime)
{
    this->cam->update(window);
    for (auto& o : gameObjects)
        o->update(deltaTime);
}

//Draws all the gameObjects
void GraphicMain::draw()
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

    for (auto& o : this->gameObjects)
        o->draw();
}

void GraphicMain::placeBoat(int x, int y, int length)
{
    GameObject* ship = new GameObject();
    ship->rotation.y = glm::radians(90.0f);
    switch (length)
    {
    case 2:
        ship->position = glm::vec3(x * tileSize + (float)length / 2.0f * tileSize, 0, y * tileSize + 0.5f * tileSize) + shipOffset;
        ship->addComponent(new GraphicModel("models/Ship2/Ship2.obj"));
        break;
    case 3:
        ship->position = glm::vec3(x * tileSize + (float)length / 2.0f * tileSize, 0, y * tileSize + 0.5f * tileSize) + shipOffset;
        ship->addComponent(new GraphicModel("models/Ship3/Ship3.obj"));
        break;
    case 4:
        ship->position = glm::vec3(x * tileSize + (float)length / 2.0f * tileSize, 0, y * tileSize + 0.5f * tileSize) + shipOffset;
        ship->addComponent(new GraphicModel("models/Ship4/Ship4.obj"));
        break;
    case 5:
        ship->position = glm::vec3(x * tileSize + (float)length / 2.0f * tileSize, 0, y * tileSize + 0.5f * tileSize) + shipOffset;
        ship->addComponent(new GraphicModel("models/Ship5/Ship5.obj"));
        break;
    default:
        std::cout << "Given ship length not valid! - GraphicMain::placeBoat" << std::endl;
        break;
    }
    this->gameObjects.push_back(ship);
}