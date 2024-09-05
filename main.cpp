#include "Particle.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <functional>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

void staticObject() {
	CircleObject object(-10, -10, 30, sf::Color(205,180,219), 0, 0);

	sf::RenderWindow window(sf::VideoMode(600,600), "Draw one object on the screen");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear();
		window.draw(object.getShape());
		window.display();
	}
}

void constantVelocityObject() {
	float dt = 0.01;

	// if we move A units buy 1 sec, then we move A*dt units by dt sec
	CircleObject object (10, 10, 30, sf::Color(205,180,219), 500*dt, 500*dt);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Draw An Object with Constant Velocity");

	bool startSimulation = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					startSimulation = !startSimulation;
		}
		if (startSimulation) {
			window.clear();
			window.draw(object.getShape());
			object.stayInsideScreen(800, 600);
			object.move(dt); // calculate the object position after dt second
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000))); //sleep for that much time before updating
		}
	}
}

void freeFallObject() {
	float dt = 0.01;

	CircleObject object (30, 30, 10, sf::Color(205,180,219), 50*dt, 50*dt);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Draw A Free Fall Object");

	bool startSimulation = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					startSimulation = !startSimulation;
		}
		if (startSimulation){
			window.clear();
			window.draw(object.getShape());
			object.accelerate(0, 981);
			object.stayInsideScreen(800, 600);
			object.move(dt); // calculate the object position after dt second
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000))); //sleep for that much time before updating
		}
	}
}

void twoObjects() {
	float dt = 0.01;
	CircleObject object1(200, 30, 10, sf::Color(205,180,219), 50*dt, 50*dt),
		object2(400, 30, 10, sf::Color(205,180,219), -30*dt, 50*dt);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Draw A Free Fall Object");

	bool startSimulation = false;

	while(window.isOpen()) {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space)
					startSimulation = !startSimulation;
			}
		}

		if (startSimulation) {
			window.clear();
			window.draw(object1.getShape());
			window.draw(object2.getShape());
			object1.accelerate(0, 981);
			object2.accelerate(0, 981);
			object1.stayInsideScreen(800, 600);
			object2.stayInsideScreen(800, 600);
			object1.collide(object2);
			object2.collide(object1);
			object1.move(dt);
			object2.move(dt);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
		}
	}
}

std::mutex objVecLock;
void addObjects(std::vector<CircleObject>& objVec, int totalNumber, int dt) {
	int color[5][3] = {{255, 214, 255}, {231, 198, 255}, {200, 182, 255}, {184, 192, 255}, {187, 209, 255}};
	int radius = 10;
	int increment = 5;
	for (int i = 0; i < totalNumber; i++) {
		if (radius == 30) increment = -5;
		else if (radius == 5) increment = 5;
		radius+=increment;
		CircleObject obj (20, 20, radius, sf::Color(color[i % 5][0], color[i%5][1], color[i%5][2]), 300 * 0.01, 0);
		{
			std::lock_guard<std::mutex> guard(objVecLock);
			objVec.push_back(obj);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
	}
}
void manyObjects() {
	float dt = 0.01;

	sf::RenderWindow window(sf::VideoMode(800,600), "Many Falling Objects");

	std::vector<CircleObject> objVec;

	bool startSimulation = false;

		std::thread addBallThread(addObjects, std::ref(objVec), 20,1 );

	while(window.isOpen()) {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					startSimulation = !startSimulation;
				}
			}
		}

			window.clear();
			for (int i = 0; i < objVec.size(); i++){
				{
					std::lock_guard<std::mutex> guard (objVecLock);
					window.draw(objVec[i].getShape());
					objVec[i].accelerate(0, 981);
					objVec[i].stayInsideScreen(800, 600);
					for (int k =7; k; k--) for (int j = 0; j < objVec.size(); j++) if (i!=j) objVec[i].collide(objVec[j]);
					objVec[i].move(dt);
					
				}
			}
		

		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
	}

	addBallThread.join();
}

int main(){
	manyObjects();
	return 0;
}
