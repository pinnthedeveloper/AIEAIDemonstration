#include "ObstacleSpawner.h"
#include "Application2D.h"

#include "Transform.h"
#include "Box.h"
#include "Circle.h"
#include "Polygon.h"
#include "PrimitiveRenderer.h"

//adds the necessary components for a obstacle object
void ObstacleSpawner::addComponents(GameObject * creation)
{
	//add all components
	Transform* transform = new Transform();
	Shape* shape = nullptr;
	Renderer* renderer = new PrimitiveRenderer();

	//the random type to give the obstacle
	ShapeType type = (ShapeType)(rand() % SHAPE_TYPE_LENGTH);

	//allocate the shape give the random type
	if (type == ShapeType::CIRCLE)
	{
		shape = new Circle();

		//random radius
		((Circle*)shape)->radius = ((rand() % 500) + 500.0f) * 0.15f;
	}
	else if (type == ShapeType::BOX)
	{
		shape = new Box();

		//random but equal half extents
		((Box*)shape)->max = Vector2(((rand() % 500) + 500.0f) * 0.1f, ((rand() % 500) + 500.0f) * 0.1f);
		((Box*)shape)->min = ((Box*)shape)->max * -1.0f;
	}
	else if (type == ShapeType::POLYGON)
	{
		shape = new Polygon();

		((Polygon*)shape)->points.push_back(Vector2(0.0f, 70.0f));
		((Polygon*)shape)->points.push_back(Vector2(80.0f, 0.0f));
		((Polygon*)shape)->points.push_back(Vector2(50.0f, -50.0f));
		((Polygon*)shape)->points.push_back(Vector2(-50.0f, -50.0f));
		((Polygon*)shape)->points.push_back(Vector2(-80.0f, 0.0f));
		
	}

	transform->translation.x = (float)(rand() % 1000);
	transform->translation.y = (float)(rand() % 1000);
	transform->scale = Vector2(1.0f, 1.0f);
	transform->rotation = 0.0f;

	Vector3 rgb = Vector3((rand() % 1000) * 0.001f, (rand() % 1000) * 0.001f, (rand() % 1000) * 0.001f).normalised();

	//assign a random colour to the obstacle
	((PrimitiveRenderer*)renderer)->r = rgb.x;
	((PrimitiveRenderer*)renderer)->b = rgb.y;
	((PrimitiveRenderer*)renderer)->g = rgb.z;
	((PrimitiveRenderer*)renderer)->depth = 3.0f;

	//linking the components together
	shape->transform = transform;
	renderer->appPtr = appPtr;
	((PrimitiveRenderer*)renderer)->shape = shape;
	((PrimitiveRenderer*)renderer)->transform = transform;

	//link the components to the game object
	transform->container = creation;
	shape->container = creation;
	renderer->container = creation;

	//add the components to the list
	creation->components.push_back(transform);
	creation->components.push_back(shape);
	creation->components.push_back(renderer);

	//register the obstacle on the blackboard
	BlackboardReference* bref = boidBlackboard->registerItemWithReference<Obstacle, Obstacle>(0.0f);
	((BlackboardData<Obstacle, Obstacle>*)bref->item)->timeLocked = true;
	((BlackboardData<Obstacle, Obstacle>*)bref->item)->data.shape = shape;

	//remove the reference as it is no longer needed
	bref->item->references.clear();
	delete bref;
}
