// Position.cpp

#include "Position.h"


// 생성자
Position::Position(int posX, int posY) : posX(posX), posY(posY){}


// 접근자
Position Position::getPosition(){
    return Position(posX, posY);
}

int Position::getPositionX() const{
    return this->posX;
}

int Position::getPositionY() const{
    return this->posY;
}


// 설정자
void Position::setPosition(int posX, int posY){
    this->posX = posX;
    this->posY = posY;
}
