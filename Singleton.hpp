
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Ensure a class has only one instance, and provide a global point of access to it.
	/*
	In software engineering, the singleton pattern is a design pattern that restricts the Instantiation of a 
	class to one object. This is useful when exactly one object is needed to coordinate actions across the system. 
	The concept is sometimes generalized to systems that operate more efficiently when only one object exists, 
	or that restrict the instantiation to a certain number of objects. The term comes from the mathematical concept
	of a singleton.

	There is criticism of the use of the singleton pattern, as some consider 
	it an anti-pattern, judging that it is overused, introduces unnecessary restrictions in situations
	where a sole instance of a class is not actually required, and introduces global state into an application.
	[1][2][3][4][5][6]

	In C++ it also serves to isolate from the unpredictability of the order of dynamic initialization, 
	returning control to the programmer.
	*/

	class Singleton {
	public:

		static Singleton& Instance()
		{
			static Singleton _obj;
			return _obj;
		}

		const char* InvokeMethod() const { return "OK"; }

	private:
		DISALLOW_COPY_AND_ASSIGN(Singleton);
	};
}

#endif