// ItemSetting.h

#ifndef __ITEMSETTING__
#define __ITEMSETTING__
#include <cstdlib>
#include <ctime>
#include "Map.h"
#include "Item.h"

class ItemSetting{
    Map& map;
public:
    ItemSetting(Map& map);

    void emergeItem(const Item& item);
    void removeItem(const Item& item);

    int itemStatus(const Item& item);

    Item makeItem(int seed);
	Item makeGate(int seed);

    Position getItemPosition(const Item& item);
};
#endif
