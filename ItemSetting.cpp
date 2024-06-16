// ItemSetting.cpp

#include "ItemSetting.h"

ItemSetting::ItemSetting(Map& map) : map(map){}

void ItemSetting::emergeItem(const Item& item){
    map.setPositionInfo(item.getItemPosition().getPositionX(), item.getItemPosition().getPositionY(), item.getType());
}

void ItemSetting::removeItem(const Item& item) {
    map.setPositionInfo(item.getItemPosition().getPositionX(), item.getItemPosition().getPositionY(), 0);
}

int ItemSetting::itemStatus(const Item& item) {
    Position pos = item.getItemPosition();
    return map.getPositionInfo(pos.getPositionX(), pos.getPositionY());
}

Item ItemSetting::makeItem(int seed) {
    int random, posX, posY;
    while(true){
        time_t t = time(NULL);
        srand(t + seed);
        random = rand() % 2;
        int w = map.getWidth();
        int h = map.getHeight();
        posX = rand() % w;
        posY = rand() % h;
        int value = map.getPositionInfo(posX, posY);
        if (value == 0) break;
    }
    return Item(POISON + random, posX, posY);
}

Item ItemSetting::makeGate(int seed) {
    int posX, posY;
    while(true) {
        time_t t = time(NULL);
        srand(t + seed);
        int w = map.getWidth();
        int h = map.getHeight();
        posX = rand() % w;
        posY = rand() % h;
        int value = map.getPositionInfo(posX, posY);
        if (value == 0 || value == 1) break;
    }
    return Item(GATE, posX, posY);
}

Position ItemSetting::getItemPosition(const Item& item) {
    return item.getItemPosition();
}
