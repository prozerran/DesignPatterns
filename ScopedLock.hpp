
#ifndef __SCOPED_LOCK_H__
#define __SCOPED_LOCK_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	class mutex_t { 
#ifdef _WIN32
	public:
		mutex_t()  { InitializeCriticalSection(&cs); }
		~mutex_t() { DeleteCriticalSection(&cs);	 }

		void Acquire() { EnterCriticalSection(&cs);  }
		void Release() { LeaveCriticalSection(&cs);  }

	private:
		CRITICAL_SECTION cs;
#else
	public:
		mutex_t(pthread_mutex_t &lock) : m_mutex(lock)  {}
		void Acquire() { pthread_mutex_lock(&m_mutex);   }
		void Release() { pthread_mutex_unlock(&m_mutex); }

	private:
		pthread_mutex_t& m_mutex;
#endif
	};

	class ScopedLock {
	public:

		ScopedLock(mutex_t& mutex) : _ref(mutex)	{ _ref.Acquire(); }
		~ScopedLock()								{ _ref.Release(); }

	private:
		ScopedLock(const ScopedLock&); // or use c++0x ` = delete`
		mutex_t& _ref;
	};
}

#endif