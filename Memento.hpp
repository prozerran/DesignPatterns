
#ifndef __MEMENTO_H__
#define __MEMENTO_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by 
	// keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.
	/*
	The memento pattern is a software design pattern that provides the ability to restore an object to its previous 
	state (undo via rollback).
	The memento pattern is implemented with two objects: the originator and a caretaker. The originator is some 
	object that has an internal state. The caretaker is going to do something to the originator, but wants to be 
	able to undo the change. 
	*/

	class Memento {
	public:
		Memento();
		void saveMember(const unsigned index,const unsigned member);
		unsigned fechtMember(const unsigned index);

	private:
		static const unsigned arraySize = 2;
		unsigned context[arraySize];
	};

	Memento::Memento() {
		this->context[0] = 0;
		this->context[1] = 0;
	}

	void Memento::saveMember(const unsigned index, const unsigned member)
	{
		this->context[index] = member;
	}

	unsigned Memento::fechtMember(const unsigned index)
	{
		return this->context[index];
	}

	class Originator {
	public:
		/*Here We declared our getters and setters*/
		void setMemberA(const unsigned valueMember);
		void setMemberB(const unsigned valueMember);
		unsigned getMemberA();
		unsigned getMemberB();

		Originator(unsigned memberA, unsigned memberB);
		void createMemento(Memento **outMem);
		void restoreMemento(Memento * const inMem);

	private:
		unsigned memberA;
		unsigned memberB;
	};

	Originator::Originator(unsigned memberA, unsigned memberB) 
		: memberA(memberA) , memberB(memberB)
	{}

	unsigned Originator::getMemberA(){ return this->memberA; }

	unsigned Originator::getMemberB(){ return this->memberB; }

	void Originator::setMemberA(const unsigned valueMember)
	{
		this->memberA = valueMember;
	}

	void Originator::setMemberB(const unsigned valueMember)
	{
		this->memberB = valueMember;
	}

	void Originator::createMemento(Memento **outMem)
	{
		Memento *p = *outMem;
		p->saveMember( 0 , this->getMemberA() );
		p->saveMember( 1 , this->getMemberB() );
	}

	void Originator::restoreMemento(Memento * const inMem)
	{
		this->setMemberA( inMem->fechtMember( 0 ) );
		this->setMemberB( inMem->fechtMember( 1 ) );
	}
}

#endif