
#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping 
	// objects from referring to each other explicitly, and it lets you vary their interaction independently.
	/*
	The mediator pattern defines an object that encapsulates how a set of objects interact. This pattern is
	considered to be a behavioral pattern due to the way it can alter the program's running behavior.
	*/

	class CPrinter {
	public:  
		void m_print(const std::string & str) const  
		{  
			std::cout << str << std::endl;  
		}  
	};  

	class CMessage {  
	public:  
		virtual ~CMessage() { }  
		virtual void m_print(const class CMediatorPattern & mediator) const;
	};  

	class CMediatorPattern {
	public:  
		CMediatorPattern(const CPrinter & pr, const CMessage & msg)
			: printer(pr), message(msg)
		{}  

		void m_print() const  
		{  
			message.m_print(*this);  
		}  
		void m_print(const std::string & str) const  
		{  
			printer.m_print(str);  
		}

	private:  
		const CPrinter & printer;  
		const CMessage & message;  
	}; 

	void CMessage::m_print(const CMediatorPattern & mediator) const  
	{  
		mediator.m_print("\tHello world!");  
	}

	void MediatorMethod(const CMediatorPattern & mediator)  
	{  
		mediator.m_print();  
	} 
}

#endif