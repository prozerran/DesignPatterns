
#ifndef __DOUBLE_CHECK_LOCKING_H__
#define __DOUBLE_CHECK_LOCKING_H__

#include "DesignPattern.h"
#include "ScopedLock.hpp"

namespace DesignPattern
{
	// Reduce the overhead of acquiring a lock by first testing the locking criterion (the 'lock hint') 
	// in an unsafe manner; only if that succeeds does the actual lock proceed. Can be unsafe when implemented 
	// in some language/hardware combinations. It can therefore sometimes be considered an anti-pattern.
	/*
	In software engineering, double-checked locking (also known as "double-checked locking optimization"[1]) is 
	a software design pattern used to reduce the overhead of acquiring a lock by first testing the locking criterion 
	(the "lock hint") without actually acquiring the lock. Only if the locking criterion check indicates that locking 
	is required does the actual locking logic proceed.

	The pattern, when implemented in some language/hardware combinations, can be unsafe. At times, it can be considered 
	an anti-pattern.[2]

	It is typically used to reduce locking overhead when implementing "lazy initialization" in a 
	multi-threaded environment, especially as part of the Singleton pattern. Lazy initialization avoids initializing 
	a value until the first time it is accessed.
	*/

	class DoubleCheckLocking {
	public:

		static DoubleCheckLocking* DoubleCheckLocking::Instance() 
		{
			DoubleCheckLocking* tmp = m_instance;

			if (tmp == NULL)				// first check
			{
				ScopedLock lock(m_mtx);		// scope-based lock, released automatically when the function returns
				tmp = m_instance;

				if (tmp == NULL)			// double check
				{
					tmp = new DoubleCheckLocking;
					m_instance = tmp;
				}
			}
			return tmp;
		}

		const char* InvokeMethod() const { return "OK"; }

	private:

		static mutex_t m_mtx;
		static DoubleCheckLocking* m_instance;

		DISALLOW_COPY_AND_ASSIGN(DoubleCheckLocking);
	};

	mutex_t DoubleCheckLocking::m_mtx;
	DoubleCheckLocking* DoubleCheckLocking::m_instance = NULL;
}

#endif