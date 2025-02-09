#ifndef OBJECT
#define OBJECT

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/CircleShape.hpp"
class Object{
	private:
		sf::Vector2f prevPos, currPos;
		sf::CircleShape obj;
	public:
		/**
		 * @input:
		 * float - radius of the object
		 * float - x position of the object
		 * float - y position of the object
		 * float - x initial velocity of the object
		 * float - y oisition of the object
		 * sf::Color - color of the object
		 */
		Object(float, float, float, float, float, sf::Color);

		/**
		 * get the actual object to draw on the screen
		 *
		 * @return
		 * sf::CircleShape& get the reference of the object.
		 */
		const sf::CircleShape& get();

		/**
		 * update the position of the object
		 *
		 * @input
		 * float - time
		 * sf::Vector2f - acceleration
		 */
		void updatePos(const float, const sf::Vector2f&);

		/**
		 * set object inside the screen
		 *
		 * @input
		 * unsigned int - width of the window
		 * unsigned int - height of the window
		 */
		void touchWall(const unsigned int, const unsigned int);
		
		/**
		 * check if this object touch another object
		 *
		 * @input
		 * Object& - the other object that wanted to be check
		 */
		void touchOther(Object&);
};

#endif
