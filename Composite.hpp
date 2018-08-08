
#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	//  Compose objects into tree structures to represent part-whole hierarchies. 
	//	Composite lets clients treat individual objects and compositions of objects uniformly.
	/*
	In software engineering, the composite pattern is a partitioning design pattern. The composite pattern describes 
	that a group of objects are to be treated in the same way as a single instance of an object. The intent of a 
	composite is to "compose" objects into tree structures to represent part-whole hierarchies. Implementing the 
	composite pattern lets clients treat individual objects and compositions uniformly.[1]

	1. Identify the scalar/primitive classes and vector/container classes
	2. 	Create an "interface" (lowest common denominator) that can make all concrete classes "interchangeable"
	3.	All concrete classes declare an "is a" relationship to the interface
	4.	All "container" classes couple themselves to the interface (recursive composition, Composite "has a" set of children up the "is a" hierarchy)
	5.	"Container" classes use polymorphism as they delegate to their children
	*/
	// 2. Create an "interface" (lowest common denominator)
	class Component {
	public:
		virtual void traverse() = 0;
	};

	class Leaf: public Component {
		// 1. Scalar class   3. "isa" relationship
	public:
		Leaf(int val)
		{
			value = val;
		}
		void traverse()
		{
			std::cout << "\t" << value << ' ';
		}

	private:
		int value;
	};

	class Composite: public Component {
		// 1. Vector class   3. "isa" relationship
	public:
		// 4. "container" class coupled to the interface
		void add(Component *ele)
		{
			children.push_back(ele);
		}
		void traverse()
		{
			for (size_t i = 0; i < children.size(); i++)
				// 5. Use polymorphism to delegate to children
				children[i]->traverse();
		}
	private:
		std::vector < Component * > children; // 4. "container" coupled to the interface
	};
}

#endif