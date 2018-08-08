
#ifndef __RAII_H__
#define __RAII_H__

#include "DesignPattern.h"

#if (_MSC_VER >= 1800)		// Visual Studio 2013

namespace DesignPattern
{
	// Ensure that resources are properly released by tying them to the lifespan of suitable objects.
	/*
	Resource Acquisition Is Initialization (RAII)[1] is a programming idiom used in several object-oriented 
	languages like C++, D, Ada and Vala. The technique was invented by Bjarne Stroustrup[2] to deal with 
	resource allocation and deallocation in C++. In this language, if an exception is thrown, and proper 
	exception handling is in place, the only code that will be executed for the current scope are the destructors 
	of objects declared in that scope. Resource management therefore needs to be tied to the lifespan of suitable 
	objects in order to gain automatic allocation and reclamation. Resources are acquired during initialization, 
	when there is no chance of them being used before they are available, and released with the destruction of 
	the same objects, which is guaranteed to take place even in case of errors.

	RAII is vital in writing exception-safe C++ code: to release resources before permitting exceptions 
	to propagate (in order to avoid resource leaks) one can write appropriate destructors once rather 
	than dispersing and duplicating cleanup logic between exception handling blocks that may or may not be executed.
	*/

	void write_to_file (const std::string & message)
	{
		// mutex to protect file access
		static std::mutex mutex;

		// lock mutex before accessing file
		std::lock_guard<std::mutex> lock(mutex);

		// try to open file
		std::ofstream file("example.txt");
		if (!file.is_open())
			throw std::runtime_error("unable to open file");

		// write message to file
		file << message << std::endl;

		// file will be closed 1st when leaving scope (regardless of exception)
		// mutex will be unlocked 2nd (from lock destructor) when leaving
		// scope (regardless of exception)
	}
}

#endif
#endif