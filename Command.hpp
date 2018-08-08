
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Encapsulate a request as an object, thereby letting you parameterize clients with different requests, 
	// queue or log requests, and support undoable operations.
	/*
	In object-oriented programming, the command pattern is a behavioral design pattern in which an object is
	used to represent and encapsulate all the information needed to call a method at a later time. 
	This information includes the method name, the object that owns the method and values for the method parameters.
	*/
	class Person;
	class Command {

	typedef void (Person::*CallbackMethod)();

	public:
		Command(Person *obj = NULL, CallbackMethod meth = NULL)
		{
			m_pObj = obj;	// the argument's name is "meth"
			callbackmethod = meth;
		}
		void execute()
		{
			if (m_pObj && callbackmethod)
				(m_pObj->*callbackmethod)();	// THE callback	
		}

	private:

		// 1. Create a class that encapsulates an object and a member function
		// a pointer to a member function (the attribute's name is "method")
		Person *m_pObj; //    
		CallbackMethod callbackmethod;
	};

	class Person {
	public:
		Person(std::string n, Command c) 
			: cmd(c), name(n)
		{}

		void talk()
		{
			// "this" is the sender, cmd has the receiver
			std::cout << "\t" << name << " is talking" << std::endl;
			cmd.execute(); // ask the "black box" to callback the receiver
		}
		void passOn()
		{
			std::cout << "\t" << name << " is passing on" << std::endl;
			// 4. When the sender is ready to callback to the receiver,
			// it calls execute()
			cmd.execute(); 
		}
		void gossip()
		{
			std::cout << "\t" << name << " is gossiping" << std::endl;
			cmd.execute();
		}
		void listen()
		{
			std::cout << "\t" << name << " is listening" << std::endl;
		}

	private:
		std::string name;
		// cmd is a "black box", it is a method invocation
		// promoted to "full object status"
		Command cmd; 
	};
}

#endif