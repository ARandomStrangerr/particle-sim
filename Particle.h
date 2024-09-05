#ifndef PARTICAL_H
#define PARTICAL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class CircleObject {
	private:
		sf::Vector2f acceleration, previousPosition, currentPosition;
		sf::CircleShape shape;
	public:
		/**
		 * default constructor
		 * @float: initial x position
		 * @float: initial y position
		 * @float: radius of the circle
		 * @sf::Color: the color of this circle
		 * @float: initial x velocity
		 * @float: initial y velocity
		 */
		CircleObject(float, float, float, sf::Color, float, float);

		/**
		 * move the object in a given time frame
		 * @float: given time frame
		 */
		void move(float);

		/**
		 * accelerate the object
		 * @flaot: accelerate at x direction
		 * @float: accelerate ay y direction
		 */
		void accelerate(float, float);

		/**
		 * make the object stay inside screen
		 * @float: upper bound x
		 * @float: upper bound y
		 */
		void stayInsideScreen(float, float);

		/**
		 * detech collision of this object with a given object
		 * @CircleObject: the other object
		 */
		void collide(CircleObject&);

		/**
		 * get the shape of this wrapper class to display on screen
		 */
		const sf::CircleShape getShape() const;
};

#endif
