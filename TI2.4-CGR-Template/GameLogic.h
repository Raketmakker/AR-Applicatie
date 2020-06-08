#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include "bord.h"
#include "Component.h"
#pragma once

using namespace std;

enum class GameState {
    STATE_NOT_STARTED,
    STATE_PLACEMENT,
    STATE_PLAYERTURN,
    STATE_AITURN,
    STATE_GAMEOVER
};

class GameLogic : public Component {
private:
    Bord bordSpeler;
    Bord bordAI;
public:
    GameState gamestate;
    vector<int> boats = {5,4,3,3,2};
    GameLogic();
    ~GameLogic();


    void GameLogic_Init();

    Bord* getBordSpeler();

    Bord* getBordAI();

    void printBords();

    virtual void update(float elapsedTime);

};

#endif
