
#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Attach additional responsibilities to an object dynamically keeping the same interface. 
	// Decorators provide a flexible alternative to subclassing for extending functionality.
	/*
	In object-oriented programming, the decorator pattern (also known as Wrapper, an alternative naming shared 
	with the Adapter pattern) is a design pattern that allows behavior to be added to an individual object,
	either statically or dynamically, without affecting the behavior of other objects from the same class.[1]
	*/

	/* Abstract base class */
	// The abstract Coffee class defines the functionality of Coffee implemented by decorator
	class Coffee {
	public:
		virtual double getCost() = 0;					// returns the cost of the coffee
		virtual std::string getIngredients() = 0;		// returns the ingredients of the coffee
		virtual ~Coffee() = 0;
	};
	inline Coffee::~Coffee() {}

	/* SimpleCoffee class. */
	// extension of a simple coffee without any extra ingredients
	class SimpleCoffee : public Coffee {
	public:
		double getCost() {
			return 1.0;
		}

		std::string getIngredients() {
			return "Coffee";
		}
	};

	/* Decorators */
	// Decorator Milk that adds milk to coffee
	class MilkDecorator : public Coffee {
	public: 
		MilkDecorator (Coffee* basicCoffee)
			:basicCoffee_(basicCoffee) {
		}

		double getCost() { // providing methods defined in the abstract superclass
			return basicCoffee_->getCost() + 0.5;
		}

		std::string getIngredients() {
			return basicCoffee_->getIngredients() + ", " + "Milk";
		}
	private:
		Coffee* basicCoffee_;
	};

	// Decorator Whip that adds whip to coffee
	class WhipDecorator : public Coffee {
	public:
		WhipDecorator (Coffee* basicCoffee)
			:basicCoffee_(basicCoffee) {
		}

		double getCost() {
			return basicCoffee_->getCost() + 0.7;
		}

		std::string getIngredients() {
			return basicCoffee_->getIngredients() + ", " + "Whip";
		}
	private:
		Coffee* basicCoffee_;
	};
}

#endif