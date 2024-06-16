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
    Item item1, item2, gate;
    int direction = LEFT;
    bool keyPressed = false;
    bool isGameOver = false;
    bool gateSpawned = false;


public:
    int stage;
    int score = 0;
    std::chrono::steady_clock::time_point startTime;

    // 생성자
    Game(WINDOW* win, int stage=1);
    void initializeStage(); // 초기화 메서드

    // 설정자
    void setSnake();
    void setItem();
    void setGate(); // 추가된 메서드

    // 화면 랜더링
    WINDOW* game_win;
    void render();
    void update();
    
    // 게임 진행
    void gameStart();
    void keyInput();

    // 게임 종료
    void gameOver();
    void gameSuccess(); // 추가된 메서드
};
#endif
