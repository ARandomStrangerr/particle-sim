#include "ScreenGrid.h"
#include "Object.h"

#include "SFML/System/Vector2.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>
#include <format>

ScreenGrid::ScreenGrid(unsigned int windowWidth,
		unsigned int windowHeight,
		unsigned int cellSize):
		cellSize(cellSize),
		windowWidth(windowWidth),
		windowHeight(windowHeight) {
	numRow = floor(windowHeight / cellSize);
	numCol = floor(windowHeight / cellSize);
}

void ScreenGrid::cleanCell() {
	cell.clear();
}

void ScreenGrid::putObjectInCell(Object* objPtr) {
	sf::Vector2f pos = {objPtr->get().getPosition().x + objPtr->get().getRadius(), objPtr->get().getPosition().y + objPtr->get().getRadius()};
	int x = floor(pos.x / cellSize),
			y = floor(pos.y / cellSize),
			linearPos = x * numCol + y;
	cell[linearPos].push_back(objPtr);
	return;
}

std::mutex itrLock;
std::unordered_map<int, std::vector<Object*>>::iterator itr;
void workerFcn(int threadNum, unsigned int width, unsigned int height, float dt, std::unordered_map<int, std::vector<Object*>>* mapPtr) {
	sf::Vector2f a ({0, 200});
	std::vector<Object*>* objVecPtr = nullptr;
	bool flag = true;
	while (true){
		{
			std::lock_guard<std::mutex> lock(itrLock);
			if (itr == mapPtr->end()){
				flag = false;
			} else {
				objVecPtr = &(itr->second);
				itr++;
			} 
		}
		if (!flag) break;
		for (int i = 0; i < objVecPtr->size(); i++){
			for (int j = 0; j < objVecPtr->size(); j++)
				if (i != j)
					(*objVecPtr)[j]->touchOther(*(*objVecPtr)[i]);
			(*objVecPtr)[i]->touchWall(width, height);
			(*objVecPtr)[i]->updatePos(dt, a);
		}
	}
}

void ScreenGrid::processObject(int numThread, float dt) {	
	itr = cell.begin();
	std::vector<std::thread> threadVec;
	for (int i = 0; i < numThread; i++) {
		threadVec.push_back(std::thread(workerFcn, i, windowWidth, windowHeight, dt, &cell));
	}
	for (int i = 0; i < numThread; i++) {
		threadVec[i].join();
	}
	return;
}
