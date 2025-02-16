#include "Object.h"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <ctime>

Object::Object(float r, float posX, float posY, float initVelcX, float initVelcY, sf::Color color): obj(r), currPos(posX, posY), prevPos(posX - initVelcX, posY - initVelcY){
	obj.setPosition(currPos);
	obj.setFillColor(color);
}

const sf::CircleShape& Object::get() const {
	return this->obj;
}

void Object::updatePos(const float dt, const sf::Vector2f& a) {
	sf::Vector2f v = currPos - prevPos;
	prevPos = currPos;
	currPos = currPos + v + a * dt * dt;
	obj.setPosition(currPos);
	return;
}

void Object::touchWall(const unsigned int width, const unsigned int height) {
	float d = obj.getRadius() * 2;
	sf::Vector2f bottomRight ({currPos.x + d, currPos.y + d});
	if (currPos.x < 0) {
		prevPos = {currPos.x , prevPos.y};
		currPos = {0, currPos.y};
	} else if (currPos.y < 0) {
		prevPos = {prevPos.x, currPos.y};
		currPos = {currPos.x, 0};
	} else if (bottomRight.x > width) {
		prevPos = {currPos.x , prevPos.y};
		currPos = {width - d, currPos.y};
	} else if (bottomRight.y > height) {
		prevPos = {prevPos.x, currPos.y};
		currPos = {currPos.x, height - d};
	}
	return;
}

void Object::touchOther(Object& other){
	sf::Vector2f distanceVec = other.currPos - currPos;
	float distanceNorm = sqrt(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
	float radiusSum = obj.getRadius() + other.obj.getRadius();
	if (distanceNorm < radiusSum) {
		sf::Vector2f unitVec = distanceVec / distanceNorm;
		float overlap = radiusSum - distanceNorm;
		currPos -= unitVec * (overlap / 2);
		other.currPos += unitVec * (overlap / 2);
	}
}
