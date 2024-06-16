#ifndef __GAME__
#define __GAME__
#include "Map.h"
#include "Snake.h"
#include "Item.h"
#include "ItemSetting.h"
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <chrono>

class Game {
    Map map;
    Snake snake;
    Item item1, item2, item3;
    Item gate1, gate2;
    int direction = LEFT;
    bool keyPressed = false;
    bool isGameOver = false;
    bool gateSpawned = false;


public:
    int stage;
    int score = 0;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::time_point<std::chrono::steady_clock> lastScoreUpdateTime;

    // 생성자
    Game(WINDOW* win, int stage=1);
    void initializeStage(); // 초기화 메서드

    // 설정자
    void setSnake();
    void setItem();
    void setGate();

    // 화면 랜더링
    WINDOW* game_win;
    void render();
    void update();
    
    // Item Method
    void modifyLength(int value);
    
    // Gate method
    void gate(Position nextHead);
    void afterGate(Position &snakeHead, Position &newGate);
    
    // Game Mission
    void mission(Position nextHead);
    void incrementScore();
    void scoreBoard();

    // 게임 진행
    void gameStart();
    void keyInput();

    // 게임 종료
    void gameOver();
    void gameSuccess();
    
    // debugging tools
    void printDebugInfo();
};
#endif
