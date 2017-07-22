#pragma once
#include <vector>

#define TEMPLATE template<typename T>

const int MAX_ENTRY = 100;

/*
* class BlackboardItem
*
* base object for an item that agents can 
* observe through the blackboard it is stored in
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class BlackboardItem
{
public:

	//name of the item
	char entry[MAX_ENTRY]; 

	//the amount of seconds remaining in this blackboard item's lifetime
	float timeRemaining = 0.0f;

	/*
	* BlackboardItem()
	* default constructor
	*/
	BlackboardItem() {};


	/*
	* ~BlackboardItem()
	* virtual function
	* default destructor
	*/
	virtual ~BlackboardItem() {};


	/*
	* getData
	* abstract function
	*
	* exposes the data held by this item
	*
	* @returns T* - pointer to the data held
	*/
	virtual void* getData() {};


	/*
	* getAnswers
	* abstract function
	*
	* exposes all responses to the data
	*
	* @returns std::vector<void*> - a list of answer pointers
	*/
	virtual std::vector<void*> getAnswers() = 0;

};