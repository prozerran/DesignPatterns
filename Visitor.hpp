
#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Represent an operation to be performed on the elements of an object structure. Visitor lets you define
	// a new operation without changing the classes of the elements on which it operates.
	/*
	In object-oriented programming and software engineering, the visitor design pattern is a way of separating an 
	algorithm from an object structure on which it operates. A practical result of this separation is the ability 
	to add new operations to existing object structures without modifying those structures. It is one way to follow 
	the open/closed principle.

	In essence, the visitor allows one to add new virtual functions to a family of classes without modifying 
	the classes themselves; instead, one creates a visitor class that implements all of the appropriate 
	specializations of the virtual function. The visitor takes the instance reference as input, and implements 
	the goal through double dispatch.
	*/

	// 1. Add an accept(Visitor) method to the "element" hierarchy
	class Element {
	public:
		virtual void accept(class Visitor &v) = 0;
	};

	class This: public Element {
	public:

		void accept(Visitor &v);
		std::string thiss() { return "This"; }
	};

	class That: public Element {
	public:

		void accept(Visitor &v);
		std::string that() { return "That"; }
	};

	class TheOther: public Element {
	public:

		void accept(Visitor &v);
		std::string theOther() { return "TheOther"; }
	};

	// 2. Create a "visitor" base class w/ a visit() method for every "element" type
	class Visitor {
	public:

		virtual void visit(This *e)		= 0;
		virtual void visit(That *e)		= 0;
		virtual void visit(TheOther *e) = 0;
	};

	void This::accept(Visitor &v)		{	v.visit(this);	}
	void That::accept(Visitor &v)		{	v.visit(this);	}
	void TheOther::accept(Visitor &v)	{	v.visit(this);	}

	// 3. Create a "visitor" derived class for each "operation" to do on "elements"
	class UpVisitor: public Visitor {
	public:

		void visit(This *e)		{ std::cout << "\tdo Up on " + e->thiss()			<< '\n';	}
		void visit(That *e)		{ std::cout << "\tdo Up on " + e->that()			<< '\n';	}
		void visit(TheOther *e) { std::cout << "\tdo Up on " + e->theOther()		<< '\n';	}
	};

	class DownVisitor: public Visitor {
	public:

		void visit(This *e)		{ std::cout << "\tdo Down on " + e->thiss()			<< '\n';	}
		void visit(That *e)		{ std::cout << "\tdo Down on " + e->that()			<< '\n';	}
		void visit(TheOther *e)	{ std::cout << "\tdo Down on " + e->theOther()		<< '\n';	}
	};
}

#endif