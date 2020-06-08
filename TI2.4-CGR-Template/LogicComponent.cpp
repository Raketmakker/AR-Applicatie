#include "LogicComponent.h"
#include <stdio.h>

LogicComponent::LogicComponent()
{
	gl.GameLogic_Init();
}

LogicComponent::~LogicComponent()
{
}

void LogicComponent::update(float elapsedTime) {
	gl.update(elapsedTime);
};