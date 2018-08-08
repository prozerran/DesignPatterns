
#ifndef __CHAIN_OF_RESPONSIBILITY_H__
#define __CHAIN_OF_RESPONSIBILITY_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. 
	// Chain the receiving objects and pass the request along the chain until an object handles it.
	/*
	In object-oriented design, the chain-of-responsibility pattern is a design pattern consisting of a source of 
	command objects and a series of processing objects.[1] Each processing object contains logic that defines the 
	types of command objects that it can handle; the rest are passed to the next processing object in the chain. 
	A mechanism also exists for adding new processing objects to the end of this chain.
	*/

	class Base {
	public:

		Base() 
			: next(0) 
		{}

		void setNext(Base *n) { next = n; }

		void add(Base *n)
		{
			if (next) 
				next->add(n);
			else
				next = n;
		}

		// 2. The "chain" method in the base class always delegates to the next obj
		virtual void handle(int i) { next->handle(i); }

	private:
		Base *next; // 1. "next" pointer in the base class
	};

	class Handler1: public Base {
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				// 3. Don't handle requests 3 times out of 4
				std::cout << "H1 passsed " << i << "  ";
				Base::handle(i); // 3. Delegate to the base class
			}
			else
				std::cout << "H1 handled " << i << "  ";
		}
	};

	class Handler2: public Base {
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				std::cout << "H2 passsed " << i << "  ";
				Base::handle(i);
			}
			else
				std::cout << "H2 handled " << i << "  ";
		}
	};

	class Handler3: public Base {
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				std::cout << "H3 passsed " << i << "  ";
				Base::handle(i);
			}
			else
				std::cout << "H3 handled " << i << "  ";
		}
	};
}

#endif