
#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
	/*
	The prototype pattern is a creational design pattern in software development. 
	It is used when the type of objects to create is determined by a prototypical instance, 
	which is cloned to produce new objects. This pattern is used to:

	- avoid subclasses of an object creator in the client application, like the abstract factory pattern does.
	- avoid the inherent cost of creating a new object in the standard way (e.g., using the 'new' keyword) when it is prohibitively expensive for a given application.

	Prototype doesn't require subclassing, but it does require an "initialize" operation. 
	Factory Method requires subclassing, but doesn't require initialization. (GoF, p116)
	*/

	class Prototype {
	public:

		std::string getType()		{ return type;		}
		int getValue()				{ return value;		}
		void Free()					{ delete this;		}
		virtual Prototype*			Clone() = 0;

	protected:

		Prototype(std::string prototype, int protovalue)
			: type(prototype), value(protovalue)
		{};

	private:

		std::string type;
		int value;
	};

	class ConcretePrototype1 : public Prototype {
	public:

		ConcretePrototype1(int number)
			: Prototype("Type1", number)
		{}

		Prototype* Clone() { return new ConcretePrototype1(*this); }
	};

	class ConcretePrototype2 : public Prototype {
	public:

		ConcretePrototype2(int number)
			: Prototype("Type2", number)
		{}

		Prototype* Clone() { return new ConcretePrototype2(*this); }
	};

	/* Factory that manages prototype instances and produces their clones. */
	class ObjectFactory {
	public:	

		static void Initialize()
		{
			if (!type1value1)
			{
				type1value1 = new ConcretePrototype1(1);
				type1value2 = new ConcretePrototype1(2);
				type2value1 = new ConcretePrototype2(1);
				type2value2 = new ConcretePrototype2(2);
			}
		}

		static void Free()
		{
			if (type1value1) delete type1value1; type1value1 = NULL;
			if (type1value2) delete type1value2; type1value2 = NULL;
			if (type2value1) delete type2value1; type2value1 = NULL;
			if (type2value2) delete type2value2; type2value2 = NULL;
		}

		static Prototype* getType1Value1() { return type1value1->Clone(); }
		static Prototype* getType1Value2() { return type1value2->Clone(); }
		static Prototype* getType2Value1() { return type2value1->Clone(); }
		static Prototype* getType2Value2() { return type2value2->Clone(); }

	private:

		static Prototype* type1value1;
		static Prototype* type1value2;
		static Prototype* type2value1;
		static Prototype* type2value2;
	};

	Prototype* ObjectFactory::type1value1 = NULL;
	Prototype* ObjectFactory::type1value2 = NULL;
	Prototype* ObjectFactory::type2value1 = NULL;
	Prototype* ObjectFactory::type2value2 = NULL;
}

#endif