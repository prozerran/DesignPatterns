
#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Convert the interface of a class into another interface clients expect. An adapter lets classes work
	// together that could not otherwise because of incompatible interfaces. The enterprise integration 
	// pattern equivalent is the translator.
	/*
	An adapter helps two incompatible interfaces to work together. This is the real world definition for an adapter. 
	Adapter design pattern is used when you want two different classes with incompatible interfaces to work together. 
	Interfaces may be incompatible but the inner functionality should suit the need. The Adapter pattern allows
	otherwise incompatible classes to work together by converting the interface of one class into an interface 
	expected by the clients.
	*/

	class Object {
	public:

		int Get_a() { return 65; }
		int Get_b() { return 66; }
		int Get_c() { return 67; }
		int Get_d() { return 68; }
		int Get_e() { return 69; }
		int Get_f() { return 70; }

		char* invoke_method() { return "OK"; }
	};

	// Adapter class can take any creational pattern, here we use private inheritance to hide/expose some methods
	class Wrapper : private Object {
	public:

		int Get_A() { return Get_a(); }
		int Get_B() { return Get_b(); }
		int Get_C() { return Get_c(); }

		int Get_X() { return Get_d() + Get_e(); }
		int Get_Y() { return Get_e() + Get_f(); }
		int Get_Z() { return Get_X() + Get_Y(); }

		const char* InvokeMethod() { return invoke_method(); }
	};
}

#endif