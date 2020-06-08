#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include "bord.h"
#include "Component.h"
#pragma once

using namespace std;
class GameLogic : public Component {

    enum class GameState {
        STATE_NOT_STARTED,
        STATE_PLACEMENT,
        STATE_PLAYERTURN,
        STATE_AITURN,
        STATE_GAMEOVER
    };

private:
    Bord bordSpeler;
    Bord bordAI;
    GameState gamestate;
public:
    GameLogic();
    ~GameLogic();


    void GameLogic_Init();

    Bord* getBordSpeler();

    Bord* getBordAI();

    void printBords();

    virtual void update(float elapsedTime);

};

#endif
