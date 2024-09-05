#include "Particle.h"
#include "SFML/System/Vector2.hpp"
#include <cmath>

CircleObject::CircleObject (float x, float y, float r, sf::Color color, float v_x, float v_y) : shape(r), previousPosition(x - v_x, y - v_y), currentPosition(x,y){
	this->shape.setPosition(currentPosition);
	this->shape.setFillColor(color);
}

void CircleObject::move(float dt){
	sf::Vector2f v = currentPosition - previousPosition;
	previousPosition = currentPosition;
	currentPosition = currentPosition + v + acceleration * dt * dt;
	this->shape.setPosition(currentPosition);
	acceleration = {0, 0}; // reset acceleration
}

void CircleObject::accelerate(float a_x, float a_y) {
	this->acceleration = {acceleration.x + a_x, acceleration.y + a_y};
}

void CircleObject::stayInsideScreen(float bound_x, float bound_y) {
	if (this->shape.getPosition().x < 0){
		this->previousPosition = {this->currentPosition.x, this->previousPosition.y};
		this->currentPosition = {0, this->currentPosition.y};
	}
	if (this->shape.getPosition().y < 0) {
		this->previousPosition = {this->previousPosition.x, this ->currentPosition.y};
		this->currentPosition = {this->currentPosition.x, 0};
	}
	if (this->shape.getPosition().x + 2 * this->shape.getRadius() > bound_x) {
		this->previousPosition = {this ->currentPosition.x, this->previousPosition.y};
		this->currentPosition = {bound_x - 2 * this->shape.getRadius(), this->currentPosition.y};
	}
	if (this->shape.getPosition().y + 2 * this->shape.getRadius() > bound_y) {
		this->previousPosition = {this->previousPosition.x, this->currentPosition.y};
		this->currentPosition = {this->currentPosition.x, bound_y - 2 * this->shape.getRadius()};
		//std::cout << shape.getRadius() << " - (" << currentPosition.x << " " << currentPosition.y << ")" << std::endl;
	}
}

void CircleObject::collide(CircleObject& other){
	sf::Vector2f centerThisShape = shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius()),
		centerOtherShape = other.shape.getPosition() + sf::Vector2f(other.shape.getRadius(), other.shape.getRadius()),
		displacement = centerOtherShape - centerThisShape;
	float displacementNorm = std::hypot(displacement.x, displacement.y);
	float minimumNorm = this->shape.getRadius() + other.shape.getRadius();
	if (displacementNorm < minimumNorm){
		float overlapNorm = minimumNorm - displacementNorm;
		sf::Vector2f corretion = displacement / displacementNorm * overlapNorm * .5f;
		this->currentPosition -= corretion;
		other.currentPosition += corretion;
		this->shape.setPosition(this->currentPosition);
		other.shape.setPosition(other.currentPosition);
	}
}

const sf::CircleShape CircleObject::getShape() const {
	return this->shape;
}
