
#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Decouple an abstraction from its implementation allowing the two to vary independently.
	/*
	The bridge pattern is a design pattern used in software engineering which is meant to 
	"decouple an abstraction from its implementation so that the two can vary independently".[1] 
	The bridge uses encapsulation, aggregation, and can use inheritance to separate responsibilities into different classes.
	*/

	/* Implemented interface. */
	class AbstractInterface {
	public:
		virtual void someFunctionality() = 0;
	};

	/* Interface for internal implementation that Bridge uses. */
	class ImplementationInterface {
	public:
		virtual void anotherFunctionality() = 0;
	};

	/* The Bridge */
	class Bridge : public AbstractInterface {
	public:

		Bridge(ImplementationInterface* backend)
		{
			implementation = backend;
		}

	protected:

		// Pimpl - Pointer to Implementation here!
		ImplementationInterface* implementation;
	};

	/* Different special cases of the interface. */

	class UseCase1 : public Bridge {
	public:

		UseCase1(ImplementationInterface* backend)
			: Bridge(backend)
		{}

		void someFunctionality()
		{
			std::cout << "\tUseCase1 on ";
			implementation->anotherFunctionality();
		}
	};

	class UseCase2 : public Bridge {
	public:

		UseCase2(ImplementationInterface* backend)
			: Bridge(backend)
		{}

		void someFunctionality()
		{
			std::cout << "\tUseCase2 on ";
			implementation->anotherFunctionality();
		}
	};

	/* Different background implementations. */

	class Windows : public ImplementationInterface {
	public:

		void anotherFunctionality()
		{
			std::cout << "Windows :-!" << std::endl;
		}
	};

	class Linux : public ImplementationInterface {
	public:

		void anotherFunctionality()
		{
			std::cout << "Linux! :-)" << std::endl;
		}
	};
}

#endif