#include "BlackboardItem.h"

#define TEMPLATE template<typename T>
#define TEMPLATE2 template<typename T, typename U>

/*
* class BlackboardData
* child class of BlackboardItem
*
* a type of information on the blackboard
* that contains information posted by one agent
*
* other agents can then respond by depositing answers
*
* finally an arbiter can then observe
* the answers and deduct the best solution
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
TEMPLATE2
class BlackboardData : public BlackboardItem
{
public:

	//information held
	T data;

	//list of responses from other agents
	std::vector<U> answers;

	/*
	* BlackboardData()
	* default constructor
	*/
	BlackboardData() {};


	/*
	* ~BlackboardData()
	* default destructor
	*/
	~BlackboardData() {};


	/*
	* getData
	* template function
	* overrides BlackboardItem's getData()
	*
	* exposes the data held by this item
	*
	* @returns T* - pointer to the data held
	*/
	T* getData() override
	{
		return &data;
	}


	/*
	* getAnswers
	* template function
	* overrides BlackboardItem's getAnswers()
	*
	* exposes all responses to the data
	*
	* @returns std::vector<U*> - a list of answer pointers
	*/
	std::vector<U*> getAnswers() override
	{
		std::vector<U*> answerPtrs = std::vector<U*>();

		//iterate through all answers, adding pointers to them to a new list
		for (size_t i = 0; i < answers.size(); i++)
		{
			answerPtrs.push_back(answers[i]);
		}

		return answerPtrs;
	}

};