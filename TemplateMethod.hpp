
#ifndef __TEMPLATE_METHOD_H__
#define __TEMPLATE_METHOD_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. 
	// Template method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
	/*
	In software engineering, the template method pattern is a behavioral design pattern that defines the program 
	skeleton of an algorithm in a method, called template method, which defers some steps to subclasses.[1] 
	It lets one redefine certain steps of an algorithm without changing the algorithm's structure.[2] 
	This use of "template" is unrelated to C++ templates.
	*/

	class TMBase {
	public:

		void a() { std::cout << "a  "; }
		void c() { std::cout << "c  "; }
		void e() { std::cout << "e  "; }

		// 2. Steps requiring peculiar implementations are "placeholders" in base class
		virtual void ph1() = 0;
		virtual void ph2() = 0;

		// 1. Standardize the skeleton of an algorithm in a base class "template method"
		void execute()
		{
			std::cout << '\t';
			a();
			ph1();
			c();
			ph2();
			e();
			std::cout << std::endl;
		}
	};

	class One: public TMBase {
	public:

		// 3. Derived classes implement placeholder methods
		void ph1() { std::cout << "b  "; }
		void ph2() { std::cout << "d  "; }
	};

	class Two: public TMBase {
	public:

		void ph1() { std::cout << "2  "; }
		void ph2() { std::cout << "4  "; }
	};
}

#endif