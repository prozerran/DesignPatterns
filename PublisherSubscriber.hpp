
#ifndef __PUBLISHER_SUBSCRIBER_H__
#define __PUBLISHER_SUBSCRIBER_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define a one-to-many dependency between objects where a state change in one object results in all 
	// its dependents being notified and updated automatically.
	/*
	In software architecture, publish–subscribe is a messaging pattern where senders of messages, called publishers, 
	do not program the messages to be sent directly to specific receivers, called subscribers. Instead, 
	published messages are characterized into classes, without knowledge of what, if any, subscribers there may be. 
	Similarly, subscribers express interest in one or more classes, and only receive messages that are of interest, 
	without knowledge of what, if any, publishers there are.
	*/

	class Publisher;
	class Subscriber {
	public:
		virtual ~Subscriber() {}
		virtual void update(Publisher* who, void* what = NULL) = 0;
	};

	class Publisher {
	public:
		Publisher() { m_notify = true; }
		virtual ~Publisher() {}
		void subscribe(Subscriber* s) { subscribers.push_back(s); }
		void unsubscribe(Subscriber* s) { subscribers.remove(s); }
		void setNotifyEnabled(bool flag) { m_notify = flag; }
		bool getNotifyEnabled() const { return m_notify; }

		void notify(void* what = NULL, Subscriber* s = NULL)
		{
			if (getNotifyEnabled())
			{
				std::list<Subscriber*>::iterator p;
				for(p = subscribers.begin(); p != subscribers.end(); p++)
					if (*p != s) (*p)->update(this, what);
			}
			setNotifyEnabled(true);
		}

	private:
		std::list<Subscriber*> subscribers;
		bool m_notify;
	};

	class MySubscriber : public Subscriber {
	public:
		virtual ~MySubscriber() {}

		// implement this to receive notification!
		virtual void update(Publisher* who, void* what = NULL)
		{
			char* str = (char*) what;
			std::cout<< "\t" << str << "\n";
		}
	};
}

#endif