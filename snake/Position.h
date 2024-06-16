// Position.h

#ifndef __POSITION__
#define __POSITION__

class Position{
    int posX, posY;
public:
    // 생성자
    Position(int posX=0, int posY=0);

    // 접근자
    Position getPosition();
    int getPositionX() const;
    int getPositionY() const;

    // 설정자
    void setPosition(int posX, int posY);
};
#endif
