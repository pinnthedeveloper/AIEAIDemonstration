#pragma once
#include "FiniteStateMachine.h"

/*
* class TradingTransition
* child class of Transition
*
* a state for the trading bot that becomes active
* when the agent accepts a trade with another trader
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class TradingTransition : public Transition
{

public:

	/*
	* TradingTransition()
	* default constructor
	*/
	TradingTransition() {}


	/*
	* ~TradingTransition()
	* default destructor
	*/
	~TradingTransition() {}


	/*
	* checkCondition
	* override's Transition's checkCondition()
	*
	* checks if the transitioning condition for
	* the transition has been met
	*
	* @returns bool - indicating if the condition was met
	*/
	bool checkCondition() override;

};