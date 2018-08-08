
#ifndef __STATE_H__
#define __STATE_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.
	/*
	The state pattern, which closely resembles Strategy Pattern, is a behavioral software design pattern,
	also known as the objects for states pattern. This pattern is used in computer programming to encapsulate 
	varying behavior for the same routine based on an object's state object. This can be a cleaner way for an object 
	to change its behavior at runtime without resorting to large monolithic conditional statements[1]:395.
	*/

	// NOTE: BUG WITH INSANE MEMORY LEAK

	class StateContext;
	class Statelike {
	public:

		virtual void writeName(StateContext* context, const std::string name) = 0;
	};

	class StateContext {
	public:

		StateContext();

		void setState(Statelike* newState) 
		{
			myState = newState;
		}
		void writeName(const std::string name) 
		{
			myState->writeName(this, name);
		}
	private:
		Statelike* myState;
	};
 
	class StateA : public Statelike {
	public:

		void writeName(StateContext* context, const std::string name);
	};
 
	class StateB : public Statelike {
	public:

		StateB() : count(0) {}
		void writeName(StateContext* context, const std::string name);

	private:
		int count;
	};

	StateContext::StateContext() 
	{
		setState(new StateA());
	}

	void StateA::writeName(StateContext* context, const std::string name)
	{
		std::string str = name;
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		std::cout << "\t" << str << std::endl;

		context->setState(new StateB());
	}

	void StateB::writeName(StateContext* context, const std::string name)
	{
		std::string str = name;
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		std::cout << "\t" << str << std::endl;

		/* Change state after StateB's writeName() gets invoked twice */
		if(++count > 1) {
			context->setState(new StateA());
		}
	}
}

#endif