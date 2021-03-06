#pragma once
#include "Component.h"
#include "MathsLibrary.h"


//forward declarations
class Transform;
class Application2D;

/*
* class Entity
* child class of Component
*
* a component that stores velocity and 
* uses it to affect the transform
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class Entity : public Component
{
public:

	//pointer to the application
	Application2D* appPtr = nullptr;

	//pointer to the required transform component
	Transform* transform = nullptr;

	//movement speed per second
	Vector2 velocity = Vector2(0, 0);

	/*
	* Entity()
	* default constructor
	*/
	Entity() {}


	/*
	* ~Entity()
	* default destructor
	*/
	~Entity() {}


	/*
	* update
	* overrides Component's update()
	*
	* gets called once per frame, updates
	* the game object's position using velocity
	*
	* @returns void
	*/
	void update() override;

};