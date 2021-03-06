#pragma once
#include "FiniteStateMachine.h"
#include "TradingAgent.h"


/*
* class GotoState
* child class of State
*
* a state for the trading bot makes the bot 
* move towards a target until it is in range
*
* author: Bradley Booth, Academy of Interactive Entertainment, 2017
*/
class GotoState : public State
{

public:

	/*
	* GotoState()
	* default constructor
	*/
	GotoState() {}


	/*
	* ~GotoState()
	* default destructor
	*/
	~GotoState() {}


	/*
	* update
	* overrides State's update(float deltaTime)
	*
	* gets called once per frame
	* while the state is active within the
	* finite state machine
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	void update(float deltaTime) override;


	/*
	* onEnter
	* overrides State's onEnter(float deltaTime)
	*
	* gets called when the finite state machine
	* transitions into this state
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	void onEnter(float deltaTime) override;


	/*
	* onExit
	* overrides State's onExit(float deltaTime)
	*
	* gets called when the finite state machine
	* transitions out of this state
	*
	* @param float deltaTime - the amount of time passed since the last frame
	* @returns void
	*/
	void onExit(float deltaTime) override;

};