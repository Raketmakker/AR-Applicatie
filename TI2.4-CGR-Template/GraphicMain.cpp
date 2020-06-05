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
    this->text = new Text(window);
    drawGrid(0, 0);
    drawGrid(1, 0);
}

//Draws the grid where the boats in sail
void GraphicMain::drawGrid(int offsetX, int offsetZ)
{
    GameObject* line;

    for (size_t x = 0; x <= gridSize; x++)
    {
        line = new GameObject();
        line->addComponent(new Line(glm::vec3(x * tileSize + offsetX * (gridSize * tileSize + tileSize), gridHeight, offsetZ * (gridSize * tileSize + tileSize)),
            glm::vec3(x * tileSize + offsetX * (gridSize * tileSize + tileSize), gridHeight, gridSize * tileSize + offsetZ * (gridSize * tileSize + tileSize)),
            glm::vec4(0, 0, 0, 1), 3.0f));
        gameObjects.push_back(line);
    }

    for (size_t z = 0; z <= gridSize; z++)
    {
        line = new GameObject();
        line->addComponent(new Line(glm::vec3(offsetX * (gridSize * tileSize + tileSize), gridHeight, z * tileSize + offsetZ * (gridSize * tileSize + tileSize)),
            glm::vec3(gridSize * tileSize + offsetX * (gridSize * tileSize + tileSize), gridHeight, z * tileSize + offsetZ * (gridSize * tileSize + tileSize)),
            glm::vec4(0, 0, 0, 1), 3.0f));
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

    this->text->draw(projection * cam->getMatrix());
}

GameObject* GraphicMain::placeBoat(int x, int y, int length)
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
    return ship;
}

void GraphicMain::firePin(int x, int z, int offsetX, int offsetZ, bool hit)
{
    GameObject* pin = new GameObject();
    pin->position = glm::vec3(x * tileSize + offsetX * gridSize * tileSize + tileSize / 2 + tileSize * offsetX,
        gridHeight + tileSize / 2, z * tileSize + offsetZ * gridSize * tileSize + tileSize / 2 + tileSize * offsetZ);
    if (hit)
    {
        pin->addComponent(new Cube(tileSize * pinSize, glm::vec4(1, 0, 0, 1)));
    }
    else
    {
        pin->addComponent(new Cube(tileSize * pinSize, glm::vec4(0, 0, 1, 1)));
    }
    gameObjects.push_back(pin);
}

void GraphicMain::test()
{
    //Test the boats
    for (size_t i = 2; i < 6; i++)
    {
        placeBoat(i, i, i);
    }

    //Test the pins on grid 0, 0
    for (size_t x = 0; x < gridSize; x++)
    {
        for (size_t z = 0; z < gridSize; z++)
        {
            if ((z + x) % 2 == 0)
            {
                firePin(x, z, 0, 0, true);
            }
            else
            {
                firePin(x, z, 0, 0, false);
            }
        }
    }
    
    //Test the pins on grid 1, 1
    for (size_t x = 0; x < gridSize; x++)
    {
        for (size_t z = 0; z < gridSize; z++)
        {
            if ((z + x) % 2 == 0)
            {
                firePin(x, z, 1, 0, false);
            }
            else
            {
                firePin(x, z, 1, 0, true);
            }
        }
    }
}