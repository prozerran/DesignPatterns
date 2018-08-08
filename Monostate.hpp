
#ifndef __MONOSTATE_H__
#define __MONOSTATE_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Variation to the Singleton Pattern
	/*
	A monostate is a "conceptual singleton" - all data members of a monostate are static, so all instances of 
	the monostate use the same (static) data. Applications using a monostate can create any number of instances 
	that they desire, as each instance uses the same data. 
	*/

	class Monostate {
	public:

		// contains only non-static member accessors

		void SetValue(int n) { s_value = n; }
		int  GetValue() { return s_value; }

		void SetString(std::string str) { s_str = str; }
		std::string& GetString() { return s_str; }

		const char* InvokeMethod() { return GetString().c_str(); }

	private:

		// contains only private static data members

		static int			s_value;
		static std::string	s_str;
	};

	int Monostate::s_value = 0;
	std::string Monostate::s_str = "";
}

#endif