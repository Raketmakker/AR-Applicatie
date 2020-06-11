#include "Input.h"

/*	Init has to be called before the update function.
	If not there will be a read acces violation (NULLPTR)
*/
void Input::init(GLFWwindow* window)
{
	this->window = window;
}
/*	Make sure this fuction is called before every other 
	update function or it will always be one frame late.
	Loops and checks every key
*/
void Input::update()
{
	for (auto& key : this->keyMap)
	{
		checkKey(key.second);
	}
}
/*	If the key is found and pressed it returns true
	If the key is not found it is added to the vector,
	and checked if it is pressed
*/
bool Input::isPressed(int glfwKey)
{
	Key* key = this->keyMap[glfwKey];
	if(key != NULL)
		return key->pressed;
	key = new Key { glfwKey, false, false };
	this->keyMap[glfwKey] = key;
	checkKey(key);
	return key->pressed;
}

void Input::checkKey(Key* key)
{
	bool keyDown = glfwGetKey(this->window, key->glfwKey) == GLFW_PRESS;
	key->pressed = keyDown && !key->pressedLastFrame;
	key->pressedLastFrame = keyDown;
}