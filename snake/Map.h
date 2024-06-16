// Map.h

#ifndef __MAP__
#define __MAP__
#include <vector>
using namespace std;

class Map{
    const int height = 21, width = 21;
    const int totalStage = 4;
	std::vector<std::vector<std::vector<int>>> totalMap;
	std::vector<std::vector<int>> map;

public:
	// 생성자
	Map(int stage = 1);

	// 접근자
	int getStageCount();
	std::vector<std::vector<int>> getMap();
    int getPositionInfo(int posX, int posY);

    int getHeight();
    int getWidth();

	// 설정자
    void setMap(int mapNumber) ;
    void setPositionInfo(int posX, int posY, int info);
};
#endif
