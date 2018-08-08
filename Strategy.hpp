
#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define a family of algorithms, encapsulate each one, and make them interchangeable. 
	// Strategy lets the algorithm vary independently from clients that use it.
	/*
	In computer programming, the strategy pattern (also known as the policy pattern) is a software design pattern,
	whereby an algorithm's behaviour can be selected at runtime. Formally speaking, the strategy pattern defines a
	family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm 
	vary independently from clients that use it.[1] 
	*/

	/** The classes that implement a concrete strategy should implement this.
	* The Context class uses this to call the concrete strategy. */

	class Strategy {
	public:

		virtual ~Strategy() {}
		virtual int execute(int a, int b) = 0; 
	};

	/** Implements the algorithm using the strategy interface */
	class Add : public Strategy {
	public:

		int execute(int a, int b)
		{
			//System.out.println("Called Add's execute()");
			return a + b;  // Do an addition with a and b
		}
	};

	class Subtract : public Strategy {
	public:

		int execute(int a, int b) 
		{
			//System.out.println("Called Subtract's execute()");
			return a - b;  // Do a subtraction with a and b
		}
	};

	class Multiply : public Strategy {
	public:

		int execute(int a, int b)
		{
			//System.out.println("Called Multiply's execute()");
			return a * b;   // Do a multiplication with a and b
		}    
	};

	// Configured with a ConcreteStrategy object and maintains
	// a reference to a Strategy object 
	class Context {
	public:

		Context(Strategy* strategy)
		{
			this->strategy = strategy;
		}

		int executeStrategy(int a, int b)
		{
			return strategy->execute(a, b);
		}

	private:
		Strategy* strategy;
	};
}

#endif