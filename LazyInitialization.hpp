
#ifndef __LAZY_INIT_H__
#define __LAZY_INIT_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Tactic of delaying the creation of an object, the calculation of a value, or some other expensive process until
	// the first time it is needed. This pattern appears in the GoF catalog as "virtual proxy", an implementation strategy for the Proxy pattern.
	/*
	Demonstrate Lazy Initialization

	Tactic of delaying the creation of an object, the calculation of a value,
	or some other expensive process until the first time it is needed.
	This pattern appears in the GoF catalog as "virtual proxy", an implementation strategy for the Proxy pattern.

	[Similarity to Multiton Pattern]
	Could be used as a global/multiple object initializer as it can be accessed anywhere and anytime.
	Very powerful since objects stays in the heap until user explicitly destroys it, so objects can be
	accessed from anywhere in the program.
	*/

	class Fruit {
	public:

		static Fruit*	Fruit::getFruit(const std::string& type);
		static void		Fruit::delFruit(const std::string& type);
		static void		Fruit::printCurrentTypes();
		static void		Fruit::delAll();

		void Fruit::Delete() { delFruit( m_type ); } ;

	private:

		static std::map<std::string,Fruit*> m_types;
		std::string m_type;

		// note: constructor private forcing one to use static getFruit()
		DISALLOW_COPY_AND_ASSIGN(Fruit);
		Fruit(const std::string& t) : m_type( t ) {}
	};

	//definition needed for using any static member variable
	std::map<std::string,Fruit*> Fruit::m_types;

	/*
	 * Lazy Factory method, gets the Fruit instance associated with a
	 * certain type. Instantiates new ones as needed.
	 * precondition: type. Any string that describes a fruit type, e.g. "apple"
	 * postcondition: The Fruit instance associated with that type.
	 */
	Fruit* Fruit::getFruit(const std::string& type)
	{
		Fruit *f = NULL;

		// try to find an existing instance; if not found std::map will return types.end()
		std::map<std::string,Fruit*>::iterator it = m_types.find(type);
 
		if (it != m_types.end())		// if instance/pointer found, return it
		{
			f = it->second;
		}

		if (f == NULL)				// instance doesn't exist, create it
		{
			f = new Fruit(type);	// lazy initialization part
			m_types[type] = f;		// adding the newly created Fruit to the types map for later lookup
		}
		return f;
	}

	void Fruit::delFruit(const std::string& type)
	{
		std::map<std::string,Fruit*>::iterator it = m_types.find(type);

		if (it != m_types.end())		// if the instance exist, remove it
		{
			Fruit* f = it->second;
			if (f) delete(f); f = NULL;
			m_types[type] = f;
			m_types.erase(it);
		}
	}

	void Fruit::delAll()
	{
		for (std::map<std::string,Fruit*>::iterator it = m_types.begin(); it != m_types.end(); )
		{
			// must move the iterator immediately, otherwise it becomes invalid after delete
			delFruit((it++)->first);
		}
		m_types.clear();
	}
 
	/*
	 * For example purposes to see pattern in action
	 */
	void Fruit::printCurrentTypes()
	{
		if (!m_types.empty())
		{
			std::cout << "\tNumber of instances made = " << m_types.size() << std::endl;
			for (std::map<std::string,Fruit*>::iterator iter = m_types.begin(); iter != m_types.end(); ++iter)
			{
				std::cout << "\t\t" << (*iter).first << std::endl;
			}
		}
	}
}  

#endif