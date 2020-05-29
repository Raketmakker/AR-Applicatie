#include "PositionTool.h"

PositionTool::PositionTool(GLFWwindow* window, float speed)
{
	this->window = window;
	this->speed = speed;
}

void PositionTool::update(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, deltaTime * speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, deltaTime * speed);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, deltaTime * speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, deltaTime * speed);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rotate(-deltaTime * speed);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rotate(deltaTime * speed);

	std::cout << "Position X: " << gameObject->position.x << " Z: " << gameObject->position.z << " Rotation: " << rotation << std::endl;
}

void PositionTool::move(float angle, float fac)
{
	gameObject->position.x += (float)cos(rotation + glm::radians(angle)) * fac;
	gameObject->position.z += (float)sin(rotation + glm::radians(angle)) * fac;
}

void PositionTool::rotate(float amount)
{
	rotation += amount;
	gameObject->rotation = glm::vec3(0, rotation, 0);
}