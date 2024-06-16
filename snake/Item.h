// Item.h

#ifndef __ITEM__
#define __ITEM__
#include "Position.h"

#define POISON 	     5
#define GROWTH 	     6
#define GATE 	     7
#define DESTINATION  8

class Item{
    int type;
    Position pos;
public:
    // 생성자
    Item(int type, Position pos);
    Item(int type=POISON, int posX=0, int posY=0);

    // 접근자
    int getType() const;
    Position getItemPosition() const;

    // 설정자
    void setItem(int type, Position pos);
};
#endif
