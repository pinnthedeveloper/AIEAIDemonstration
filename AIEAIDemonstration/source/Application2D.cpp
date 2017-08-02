#include "Application2D.h"

#include <iostream>
#include <Windows.h>

//constructor
Application2D::Application2D()
{
}


//destructor
Application2D::~Application2D()
{
}


//runs when the game is told to run
bool Application2D::startup()
{
	ZeroMemory(resourceFolder, FILENAME_MAX);

	//get the path to the bin folder
	GetModuleFileName(NULL, resourceFolder, sizeof(resourceFolder) - 1);

	//find the first backslash from the right
	char* slash = strrchr(resourceFolder, '\\');

	//cut the string at the slash, leaving only the bin folder path and not the .exe
	*slash = '\0';

	//add the resources folder to the path
	strcat_s(resourceFolder, "\\resources\\");

	//create the renderer
	m_renderer2D = new aie::Renderer2D();

	//create the director and spawner/s
	director = new Director();
	testSpawner = new TestSpawner();
	tradingBotSpawner = new TradingBotSpawner();
	//navigationBotSpawner = new NavigationBotSpawner();

	//link them to each other and the application
	director->appPtr = this;
	testSpawner->appPtr = this;
	tradingBotSpawner->appPtr = this;
	//navigationBotSpawner->appPtr = this;

	//create a blackboard that can hold 500 messages
	tradingBlackboard = new Blackboard(500);

	//create the navmesh
	navMesh = new NavMesh();

	//link the navigation bot spawner to the navmesh
	//navigationBotSpawner->navMesh = navMesh;
	
	//link the pathfinder to the game
	navMesh->appPtr = this;
	navMesh->heursticFunction = &EuclideanDistance;
	
	//load the nav mesh from file
	char navMeshPath[FILENAME_MAX];

	strcpy_s(navMeshPath, resourceFolder);
	strcat_s(navMeshPath, "meshes\\mesh2.txt");

	navMesh->load(navMeshPath);

	director->employee = tradingBotSpawner;

	//spawn 18 trading bots
	for (int i = 0; i < 0; i++)
	{
		gameObjects.push_back(director->createGameObject());
	}

	return true;
}


//runs when the game is exited
void Application2D::shutdown()
{
	//delete the director and the spawner/s
	delete director;
	delete testSpawner;

	delete tradingBlackboard;
	delete navMesh;

	//iterate through all gameobjects, deleting each one
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
}

float decayTimer = 0.0f;
float decayDuration = 0.0f;

std::vector<Vector2> path;
Vector2 start = Vector2(0, 0);
Vector2 end = Vector2(0, 0);

//the game loop
void Application2D::update(float deltaTime)
{
	m_deltaTime = deltaTime;

	aie::Input* input = aie::Input::getInstance();

	//shut down the application if the escape key is pressed
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}

	tradingBlackboard->update(deltaTime);

	//iterate through all gameobjects, updating each one
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}

	if (input->isMouseButtonDown(0))
	{
		start = Vector2(input->getMouseX(), input->getMouseY());
	}

	if (input->isMouseButtonDown(1))
	{
		end = Vector2(input->getMouseX(), input->getMouseY());
	}


	decayTimer -= deltaTime;

	if (decayTimer <= 0.0f)
	{
		decayTimer = decayDuration;

		path = navMesh->findPath(start, end);
	}
}


//the render routine, runs after the game
void Application2D::draw()
{
	clearScreen();

	m_renderer2D->begin();

	m_renderer2D->setRenderColour(1, 1, 1);

	//iterate through all gameobjects, drawing each one
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}

	navMesh->drawMesh(5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	m_renderer2D->setRenderColour(0, 1, 0);

	for (int i = 0; i < (int)path.size() - 1; i++)
	{
		m_renderer2D->drawLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y, 2.0f, 0.0f);
	}

	m_renderer2D->end();
}
