
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <queue>
#include "ScopedLock.hpp"
#include "Thread.hpp"

namespace DesignPattern
{
	typedef int Task;
	typedef std::queue<Task> TaskQueue;

	// some static globals
	static mutex_t		s_thr_mtx;
	static TaskQueue	s_task_queue;

	class TaskThread : public Thread {
	public:

		// implement your own execution here!
		void Run(void* data = NULL)
		{
			while (s_task_queue.size() > 0)
			{
				Thread::Sleep(100);

				// Critical Section, allow only ONE thread to execute in here
				{
					ScopedLock lock(s_thr_mtx);

					if (s_task_queue.size() > 0)
					{
						Task t = s_task_queue.front();

						// do your task here!
						printf("\t%s : pop %d\n", 
							GetThreadName().c_str(), t);

						s_task_queue.pop();
					}
				}
			}
		}
	};

	class ThreadPool {
	public:

		explicit ThreadPool(int num_thr)
			: m_pThr(NULL), m_num_threads(num_thr)
		{}

		~ThreadPool()
		{
			if (m_pThr)
			{
				for (int i = 0; i < m_num_threads; i++)
					delete m_pThr[i];

				delete [] m_pThr;
				m_pThr = NULL;
			}
		}

		void AddTask(Task& task)
		{
			s_task_queue.push(task);
		}

		void ProcessPool()
		{
			m_pThr = new TaskThread*[m_num_threads];

			// run each task in the queue specified by number of pool threads
			for (int i = 0; i < m_num_threads; i++)
			{
				char thr_name[32] = {0};
				sprintf_s(thr_name, sizeof(thr_name), "Thread %d", i);

				m_pThr[i] = new TaskThread;
				m_pThr[i]->SetThreadName(thr_name);
				m_pThr[i]->Start();
			}

			// wait until all task completed
			for (int i = 0; i < m_num_threads; i++)
			{
				m_pThr[i]->Join();
			}
		}

	private:
		
		int				m_num_threads;
		TaskThread**	m_pThr;
	};
}

#endif
