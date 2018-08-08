
#ifndef __REGISTER_CALLBACK_H__
#define __REGISTER_CALLBACK_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Simple version of Publisher/Subscriber

	typedef void (*ObjectCallback)(void*, void*);

	class ObjectManager {
	public:

		ObjectManager()
			: CallBackFunc(NULL), m_cb_userdata(NULL)
		{}

		void ObjectManager::RegisterCallback( ObjectCallback callback = NULL, void* userdata = NULL )
		{
			CallBackFunc = callback;
			m_cb_userdata= userdata;
		}

		void NotifyCallback()
		{
			if (CallBackFunc)
				CallBackFunc(this, m_cb_userdata);
		}

	private:

		ObjectCallback CallBackFunc;
		void* m_cb_userdata;
	};

	// This is the user defined callback within class
	class MyObject {
	public:

		// This is user the defined callback method!
		static void MyCallbackMethod(void* ob_param, void* userdata)
		{
			// user data can be anything!
			MyObject* pObj = static_cast<MyObject*>(userdata);
			if (pObj) pObj->InvokeMethod();
		}

	private:

		void InvokeMethod() { std::cout << "\tHello World\n"; }
	};

	// This is user the defined callback method!
	void MyCallbackMethod(void* ob_param, void* userdata)
	{
		const char* str = (const char*) userdata;
		std::cout << "\t" << str;
	}
}

#endif