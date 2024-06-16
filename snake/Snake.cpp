// Snake.cpp

#include "Snake.h"


// 생성자
Snake::Snake(Position pos, int snakeLength, int snakeDirection) : snakeDirection(snakeDirection) {
    for (int i=0; i<snakeLength; ++i){
        snakeBody.push_back(pos);
        switch (snakeDirection) {
            case UP:
                pos.setPosition(pos.getPositionX(), pos.getPositionY() + 1);
                break;
            case DOWN:
                pos.setPosition(pos.getPositionX(), pos.getPositionY() - 1);
                break;
            case LEFT:
                pos.setPosition(pos.getPositionX() + 1, pos.getPositionY());
                break;
            case RIGHT:
                pos.setPosition(pos.getPositionX() - 1, pos.getPositionY());
                break;
        }
    }
}


// 접근자
int Snake::getSnakeLength() {
    return snakeBody.size();
}

int Snake::getSnakeDirection() {
    return snakeDirection;
}

std::deque<Position> Snake::getSnakeBody() {
    return snakeBody;
}

Position Snake::getHeadPosition() {
    return snakeBody.front();
}

Position Snake::getTailPosition() {
    return snakeBody.back();
}


// 설정자
void Snake::setSnakePosition(int posX, int posY) {
    snakeBody.front().setPosition(posX, posY);
}


// 위치 이동
void Snake::move() {
    Position updateHead = getHeadPosition();
    switch (snakeDirection) {
        case UP:
            updateHead.setPosition(updateHead.getPositionX(), updateHead.getPositionY() - 1);
            break;
        case DOWN:
            updateHead.setPosition(updateHead.getPositionX(), updateHead.getPositionY() + 1);
            break;
        case LEFT:
            updateHead.setPosition(updateHead.getPositionX() - 1, updateHead.getPositionY());
            break;
        case RIGHT:
            updateHead.setPosition(updateHead.getPositionX() + 1, updateHead.getPositionY());
            break;
    }
    snakeBody.push_front(updateHead);
    snakeBody.pop_back();
}


// 꼬리 제거 함수
void Snake::removeTail() {
    if (!snakeBody.empty()) {
        snakeBody.pop_back();
    }
}

// 꼬리 추가 함수
void Snake::addTail(Position newTail) {
    snakeBody.push_back(newTail);
}


// 상태 갱신
Position Snake::updateHead(){
    Position updateHead = getHeadPosition();
    switch (snakeDirection) {
        case UP:
            updateHead.setPosition(updateHead.getPositionX(), updateHead.getPositionY() - 1);
            break;
        case DOWN:
            updateHead.setPosition(updateHead.getPositionX(), updateHead.getPositionY() + 1);
            break;
        case LEFT:
            updateHead.setPosition(updateHead.getPositionX() - 1, updateHead.getPositionY());
            break;
        case RIGHT:
            updateHead.setPosition(updateHead.getPositionX() + 1, updateHead.getPositionY());
            break;
    }
    return updateHead;
}

void Snake::updateDirection(int newDirection) {
    this->snakeDirection = newDirection;
}
