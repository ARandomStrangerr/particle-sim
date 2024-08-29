#include "Particle.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <thread>
#include <chrono>

void staticObject() {
	CircleObject object(10, 10, 30, sf::Color(205,180,219), 0, 0);

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
	float dt = 0.06;

	// if we move A units buy 1 sec, then we move A*dt units by dt sec
	CircleObject object (10, 10, 30, sf::Color(205,180,219), 50*dt, 50*dt);

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
			object.move(dt); // calculate the object position after dt second
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000))); //sleep for that much time before updating
		}
	}
}

void freeFallObject() {
	float dt = 0.01;

	CircleObject object (10, 10, 10, sf::Color(205,180,219), 0, 0);

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

int main(){
	constantVelocityObject();
	return 0;
}
