#pragma once

#include "Component.h"
#include "GameLogic.h"

class LogicComponent : public Component
{
private:
	GameLogic gl;
public:
	LogicComponent();
	~LogicComponent();
	virtual void update(float elapsedTime);
};

