
#ifndef __THREAD_H__
#define __THREAD_H__

namespace DesignPattern
{
	class Thread {
	public:

		Thread()
			: m_hThread(NULL), m_dThreadId(-1), m_thread_name("")
		{}
		
		~Thread()
		{
			RemoveThread();
		}

		void Start(void* data = NULL)
		{
			if (!m_hThread)
			{
				m_user_data = data;
				m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadStart, this, 0, &m_dThreadId);
			}
		}

		void Join(long time_out_msec = -1)
		{
			if (time_out_msec >= 0)
				WaitForSingleObject(m_hThread, time_out_msec);
			else
				WaitForSingleObject(m_hThread, INFINITE);
		}

		void SetThreadName(const char* s_name) { m_thread_name.append(s_name); }
		const std::string& GetThreadName() const { return m_thread_name; }

		DWORD GetThreadId() const { return m_dThreadId; }

		// all child classes must override this method
		virtual void Run(void* data = NULL) = 0;

		virtual void OnRunDone()
		{
			RemoveThread();
		}

		static void Sleep(DWORD msec) { ::Sleep(msec); }

	private:

		void RemoveThread()
		{
			if (m_hThread)
			{
				CloseHandle(m_hThread);
				m_hThread = NULL;
			}
		}

		void* GetUserData() const { return m_user_data; }

		static void ThreadStart(Thread* pObj)
		{
			pObj->Run(pObj->GetUserData());
			pObj->OnRunDone();
		}

	private:

		HANDLE		m_hThread;
		DWORD		m_dThreadId;
		void*		m_user_data;
		std::string	m_thread_name;
	};

	// implement your own thread class that inherits from Thread
	class MyThread : public Thread {
	public:

		void Run(void* data = NULL)
		{
		// TODO: put your run code here!
		//	printf("Hello World\n");
		}
	};
}

#endif
