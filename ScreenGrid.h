#ifndef SCREEN_GRID
#define SCREEN_GRID

#include <unordered_map>
#include <vector>

#include "Object.h"

class ScreenGrid{
	private:
		unsigned int cellSize, windowWidth, windowHeight, numRow, numCol;
		std::unordered_map<int, std::vector<Object*>> cell;
	public:
		ScreenGrid(unsigned int, unsigned int, unsigned int);
		void cleanCell();
		void putObjectInCell(Object*);
		void processObject(int, float);
};
#endif
