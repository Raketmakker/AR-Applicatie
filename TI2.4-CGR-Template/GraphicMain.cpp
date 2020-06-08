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
    GameObject* textGameObject = new GameObject();
    this->text = new Text();
    textGameObject->addComponent(this->text);
    this->gameObjects.push_back(textGameObject);
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
}

//Place a boat on the player grid
GameObject* GraphicMain::placeBoat(int x, int z, int length)
{
    GameObject* ship = new GameObject();
    ship->rotation.y = glm::radians(90.0f);
    switch (length)
    {
    case 2:
        setBoatPosition(ship, x, z, length);
        ship->addComponent(new GraphicModel("models/Ship2/Ship2.obj"));
        break;
    case 3:
        setBoatPosition(ship, x, z, length);
        ship->addComponent(new GraphicModel("models/Ship3/Ship3.obj"));
        break;
    case 4:
        setBoatPosition(ship, x, z, length);
        ship->addComponent(new GraphicModel("models/Ship4/Ship4.obj"));
        break;
    case 5:
        setBoatPosition(ship, x, z, length);
        ship->addComponent(new GraphicModel("models/Ship5/Ship5.obj"));
        break;
    default:
        std::cout << "Given ship length not valid! - GraphicMain::placeBoat" << std::endl;
        break;
    }
    this->gameObjects.push_back(ship);
    return ship;
}

//Set the position of the given boat on player grid
void GraphicMain::setBoatPosition(GameObject* ship, int x, int z, int length)
{
    if (length >= 2 && length <= 5)
    {
        ship->position = glm::vec3(x * tileSize + (float)length / 2.0f * tileSize, 0, z * tileSize + 0.5f * tileSize) + shipOffset;
    }
    else
    {
        std::cout << "Given ship length not valid! - GraphicMain::setBoatPosition" << std::endl;
    }
}

//Fire a pin at the given coordinates
GameObject* GraphicMain::firePin(int x, int z, int offsetX, int offsetZ)
{
    GameObject* pin = new GameObject();
    setPinPosition(pin, x, z, offsetX, offsetZ);
    pin->addComponent(new Cube(tileSize * pinSize, glm::vec4(0.0f, 1.0f, 64.0f / 255.0f, 1.0f)));
    gameObjects.push_back(pin);
    return pin;
}

//Set the given pin at the given coordinates
void GraphicMain::setPinPosition(GameObject* pin, int x, int z, int offsetX, int offsetZ)
{
    pin->position = glm::vec3(x * tileSize + offsetX * gridSize * tileSize + tileSize / 2 + tileSize * offsetX,
        gridHeight + tileSize / 2, z * tileSize + offsetZ * gridSize * tileSize + tileSize / 2 + tileSize * offsetZ);
}

//Changes the color of the given pin. If hit -> red, else -> cyan
void GraphicMain::setPinHit(GameObject* pin, bool hit)
{
    Cube* cube = pin->getComponent<Cube>();
    if (cube != nullptr)
    {
        if (hit)
        {
            cube->setColor(glm::vec4(1, 0, 0, 1));
        }
        else
        {
            cube->setColor(glm::vec4(0, 1, 1, 1));
        }
    }
}

void GraphicMain::test()
{
    //Test the boats
    for (size_t i = 2; i < 6; i++)
    {
        placeBoat(i, i, i);
    }
    GameObject* pin;
    //Test the pins on grid 0, 0
    for (size_t x = 0; x < gridSize; x++)
    {
        for (size_t z = 0; z < gridSize; z++)
        {
            if ((z + x) % 2 == 0)
            {
                pin = firePin(x, z, 0, 0);
                setPinHit(pin, true);
            }
            else
            {
                pin = firePin(x, z, 0, 0);
                setPinHit(pin, false);
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
                pin = firePin(x, z, 1, 0);
                //setPinHit(pin, false);
            }
            else
            {
                pin = firePin(x, z, 1, 0);
                setPinHit(pin, true);
            }
        }
    }

    //Text test
    this->text->setText({ "Test line 1", "Test line 2 (selected)", "Test line 3" });
    this->text->setSelected(1);
}