#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "Object.h"
#include "ScreenGrid.h"

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"

std::mutex lockObj;
std::vector<Object> objs;

void addObject(int objNum) {
	std::vector<std::vector<int>> color = {{56, 102, 65}, {106, 153, 78}, {167, 201, 87}, {242, 232, 207}, {188, 71, 73}};
	for (int i = 0; i < objNum; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(220));
		int colorIndex = i % 5;
		Object obj (10 + (i * 2) % 5 , 100, 10, 5, 0, sf::Color(color[colorIndex][0], color[colorIndex][1], color[colorIndex][2]));
		std::lock_guard<std::mutex> lock(lockObj);
		objs.push_back(obj);
	}
}

void one(){
	sf::Font font;
	if (!font.loadFromFile("/Library/Fonts/ProggyClean/ProggyCleanCENerdFont-Regular.ttf")) return;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(10,10);
	
	sf::Vector2f a ({0, 200});
	
	float targetDt = 1.f/60.f;
	
	unsigned int width = 800, height = 600;
	sf::RenderWindow window (sf::VideoMode(width, height), "Display Single Object");
	
	std::thread addBallWorker(addObject, 800);
	ScreenGrid screenGridWorker(width, height, 100);

	auto lastTimeStamp = std::chrono::high_resolution_clock::now();
	while (window.isOpen()){
		auto firstTimeStamp = std::chrono::high_resolution_clock::now();

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear();
		auto currTimeStamp = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float>(currTimeStamp - lastTimeStamp).count();
		lastTimeStamp = currTimeStamp;
		
		{
			std::lock_guard<std::mutex> lock(lockObj);
			screenGridWorker.cleanCell();
			for (int i = 0; i < objs.size(); i++){
				screenGridWorker.putObjectInCell(&objs[i]);
			}
			screenGridWorker.processObject(2, dt);
			for (int i = 0; i < objs.size(); i++) {
				window.draw(objs[i].get());
			}
		}

		float fps = 1.f / dt;
		text.setString(std::to_string((int) fps));
		window.draw(text);
		window.display();

		auto lastTimeStamp = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float>(lastTimeStamp - firstTimeStamp).count();
		if (dt < targetDt) {
			float sleepTime = 	targetDt - dt;
			std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
		}
	}
	addBallWorker.join();
}

int main() {
	one();
	return 0;
};
