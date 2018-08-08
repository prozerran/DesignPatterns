
#ifndef __NULL_OBJECT_H__
#define __NULL_OBJECT_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Avoid null references by providing a default object.
	/*
	In object-oriented computer programming, a Null Object is an object with defined neutral ("null") behavior. 
	The Null Object design pattern describes the uses of such objects and their behavior (or lack thereof). 
	It was first published in the Pattern Languages of Program Design book series.[1] 
	*/

	class IAnimal {
	public:
		virtual void make_sound() = 0;
	};

	class Dog : public IAnimal {
	public:
		void make_sound() { std::cout << "\twoof!" << std::endl; }
	};

	class Cat : public IAnimal {
	public:
		void make_sound() { std::cout << "\tmeew!" << std::endl; }
	};

	// Null Object
	class Null_Animal : public IAnimal {
	public:
		void make_sound() { }	// do nothing!
	};
}

#endif