
#ifndef __MULTITON_H__
#define __MULTITON_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Ensure a class has only named instances, and provide global point of access to them.
	// The Multiton pattern expands on the singleton concept to manage a map of named instances as key-value pairs.
	/*
	In software engineering, the multiton pattern is a design pattern similar to the singleton,
	which allows only one instance of a class to be created. The multiton pattern expands on the singleton concept 
	to manage a map of named instances as key-value pairs.

	Rather than have a single instance per application (e.g. the java.lang.Runtime object in the Java programming language)
	the multiton pattern instead ensures a single instance per key.

	Most people and textbooks consider this a singleton pattern[citation needed]. 
	For example, multiton does not explicitly appear in the highly regarded object-oriented programming 
	text book Design Patterns (it appears as a more flexible approach named registry of singletons).
	*/

	template <typename T, typename Key = std::string>
	class Multiton {
	public:

		static void destroy()
		{
			for (typename std::map<Key, T*>::const_iterator it = _map_inst.begin(); it != _map_inst.end(); ++it)
				delete (*it).second;

			_map_inst.clear();
		}

		static T* getPtr(const Key& key)
		{
			typename std::map<Key, T*>::const_iterator it = _map_inst.find(key);

			if (it != _map_inst.end())
			{
				return (T*)(it->second);
			}

			T* instance = new T();
			_map_inst[key] = instance;
			return instance;
		}

		static T& getRef(const Key& key)
		{
			return *getPtr(key);
		}

	protected:

		Multiton() {}
		~Multiton() {}

	private:

		Multiton(const Multiton&) {}
		Multiton& operator= (const Multiton&) { return *this; }

		static std::map<Key, T*> _map_inst;
	};

	template <typename T, typename Key>
	std::map<Key, T*> Multiton<T, Key>::_map_inst;
}

#endif