
#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Avoid expensive acquisition and release of resources by recycling objects that are no longer in use. 
	// Can be considered a generalisation of connection pool and thread pool patterns.
	/*
	The object pool pattern is a software creational design pattern that uses a set of initialized objects kept 
	ready to use, rather than allocating and destroying them on demand. A client of the pool will request an 
	object from the pool and perform operations on the returned object. When the client has finished, it returns 
	the object, which is a specific type of factory object, to the pool rather than destroying it.
	*/

	class Resource {
	public:

		Resource()
			: value(0)
		{}

		void  reset()				{ value = 0; }
		void  setValue(int number)	{ value = number; }
		int	  getValue()			{ return value; }

	private:
		int value;
	};

	/* Note, that this class is a singleton. */
	class ObjectPool {
	public:

		static ObjectPool& getInstance()
		{
			static ObjectPool _obj;
			return _obj;
		}

		Resource* getResource()
		{
			if (resources.empty())
			{
				//std::cout << "Creating new." << std::endl;
				return new Resource;
			}
			else
			{
				//std::cout << "Reusing existing." << std::endl;
				Resource* resource = resources.front();
				resources.pop_front();
				return resource;
			}
		}

		void returnResource(Resource* object)
		{
			object->reset();
			resources.push_back(object);
		}

	private:

		std::list<Resource*> resources;
		DISALLOW_COPY_AND_ASSIGN(ObjectPool);
	};
}

#endif