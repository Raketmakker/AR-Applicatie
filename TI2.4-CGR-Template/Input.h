#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <iterator> 
#include <map> 

/*  Class to easely check if a button has been pressed once.
    Usage: initialize class with window. Update class every
    frame BEFORE the other update functions. Ask in the other
    update functions for the keys.
*/

struct Key
{
    int glfwKey = -1;
    bool pressedLastFrame = false;
    bool pressed = false;
};

class Input
{
private:
    Input() {}
    GLFWwindow* window;
    void checkKey(Key* key);
    std::map<int, Key*> keyMap;
public:
    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
    static Input& getInstance()
    {
        static Input instance;
        return instance;
    }
    void init(GLFWwindow* window);
    void update();
    bool isPressed(int glfwKey);
};
