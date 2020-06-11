#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include "bord.h"
#include "Component.h"
#include "GraphicMain.h"
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
    GraphicMain* gm;
    GameState gamestate;
    vector<int> boats = {5,4,3,3,2};
    vector<int> boatsAI = {5,4,3,3,2};
    GameLogic();
    GameLogic(GraphicMain* graphicMain);
    ~GameLogic();


    void GameLogic_Init();

    Bord* getBordSpeler();

    Bord* getBordAI();

    void initBordAI();

    void printBords();

    bool checkIfGameIsOver();

    virtual void update(float elapsedTime);

};

#endif
