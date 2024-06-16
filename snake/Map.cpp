// Map.cpp

#include "Map.h"

// 생성자
Map::Map(int stage){
	totalMap = {
    	{
    		// 첫 번째 맵 (일정 score 이상 획득하기)
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
    	},
    	{
        	// 두 번째 맵 (십자 맵에서 일정 score 이상 획득하기)
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
    	},
    	{
        	// 세 번째 맵 (double square 맵에서 일정 score 이상 획득하기)
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
    	},
    	{
        	// 네 번째 맵 (미로 찾기 - 미로 끝 지점 item 을 head 가 획득할 경우 미션 성공)
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,8,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
    	}
	};
	setMap(stage);
}


// 접근자
int Map::getStageCount() {
    return totalStage;
}

std::vector<std::vector<int>> Map::getMap() {
    return map;
}
int Map::getPositionInfo(int posX, int posY) {
    return map[posY][posX];
}

int Map::getHeight(){
    return this->height;
}

int Map::getWidth(){
    return this->width;
}

// 설정자
void Map::setMap(int stage) {
    map = totalMap[stage - 1];
}

void Map::setPositionInfo(int posX, int posY, int info) {
    map[posY][posX] = info;
}
