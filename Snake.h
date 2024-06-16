// Snake.h

#ifndef __SNAKE__
#define __SNAKE__
#include "Position.h"
#include <deque>

#define HEAD 3
#define TAIL 4

#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14

class Snake{
    std::deque<Position> snakeBody;
    int snakeDirection;

public:
    // 생성자
    Snake(Position pos = Position(0, 0), int snakeLength = 3, int snakeDirection = LEFT);

    // 접근자
    int getSnakeLength();
    int getSnakeDirection();
    std::deque<Position> getSnakeBody();
    Position getHeadPosition();
    Position getTailPosition();

    // 설정자
    void setSnakePosition(int posX = 0, int posY = 0);

    // 위치 이동
    void move();

    // 꼬리 길이 조절
    void removeTail();
    void addTail(Position newTail);

    // 상태 갱신
    Position updateHead();
    void updateDirection(int newDirection);
};
#endif
