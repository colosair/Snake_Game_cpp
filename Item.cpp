// Item.cpp

#include "Item.h"

Item::Item(int type, Position pos) : type(type), pos(pos){}

Item::Item(int type, int posX, int posY) : type(type), pos(Position(posX, posY)){}

int Item::getType() const{
    return this->type;
}

Position Item::getItemPosition() const{
    return this->pos;
}

void Item::setItem(int type, Position pos){
    this->type = type;
    this->pos = pos;
}