
#ifndef __FLYWEIGHT_H__
#define __FLYWEIGHT_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Use sharing to support large numbers of similar objects efficiently.
	/*
	In computer programming, flyweight is a software design pattern. A flyweight is an object that minimizes 
	memory use by sharing as much data as possible with other similar objects; it is a way to use objects in 
	large numbers when a simple repeated representation would use an unacceptable amount of memory. Often some parts 
	of the object state can be shared, and it is common practice to hold them in external data structures and pass
	them to the flyweight objects temporarily when they are used.
	*/

	class Gazillion	{
	public:
		Gazillion(int value_one)
		{
			m_value_one = value_one;
			std::cout << "\tctor: " << m_value_one << '\n';
		}
		~Gazillion()
		{
			std::cout << m_value_one << ' ';
		}
		void report(int value_two)
		{
			std::cout << "\t" << m_value_one << value_two << ' ';
		}
	private:
		int m_value_one;
	};

	class Factory {
	public:
		static Gazillion *get_fly(int in)
		{
			if (!s_pool[in])
				s_pool[in] = new Gazillion(in);
			return s_pool[in];
		}
		static void clean_up()
		{
			for (int i = 0; i < X; ++i)
				if (s_pool[i])
					delete s_pool[i];
		}
		static int X, Y;
	private:
		static Gazillion *s_pool[];
	};

	int Factory::X = 6, Factory::Y = 10;
	Gazillion *Factory::s_pool[] = { 0, 0, 0, 0, 0, 0 };
}

#endif