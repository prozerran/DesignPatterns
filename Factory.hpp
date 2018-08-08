
#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define an interface for creating a SINGLE object, but let subclasses decide which class to instantiate.
	// Factory Method lets a class defer instantiation to subclasses (dependency injection[16]).
	/*
	There are many scenarios when a class needs to create several objects.
	The class can do so freely but it has to know about each and every class.
	There is a possibility that the class can't anticipate all the objects it needs to create.
	The second scenario could be that the class wants to delegate the responsibility of creating the objects 
	to its subclasses or perhaps some helper functions.

	If we have any of the above mentioned scenarios, we can have the Factory pattern.
	The idea of the factory pattern is to have the classes ability to create other classes without them knowing 
	about all the possible classes that exists. This gives us extensibility. 
	With factory pattern, we get the possibility of creating, maintaining and manipulating a collection of different 
	objects that have some common characteristics. The main use of this pattern is in classes that manage a lot 
	of objects like Document Manager, Control manager, Facility Manager.

	GOF defines factory pattern as "Define an interface for creating an object, 
	but let subclasses decide which class to instantiate. Factory pattern lets a 
	class defer instantiation to subclasses". 
	*/

	// the interface class
	class IEmployee {
	public:

		enum EMP_TYPE
		{
			ENGINEER,
			MANAGER
		};

		virtual ~IEmployee() {};
		virtual void Free() { delete this; }

		static IEmployee* CreateEmployee(EMP_TYPE etype);
	};

	// factory object/product
	class Manager : public IEmployee {
	public:

		Manager() {} ;
	};

	// factory object/product
	class Engineer : public IEmployee {
	public:

		Engineer() {} ;
	};

	// static CreateObject factory method !!!
	IEmployee* IEmployee::CreateEmployee(EMP_TYPE etype)
	{
		switch (etype)
		{
		case MANAGER:
			return new Manager();
			break;

		case ENGINEER:
			return new Engineer();
			break;

		default:
			break;
		}
		return NULL;
	}
}

#endif