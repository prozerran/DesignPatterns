
#ifndef __ABSTRACT_FACTORY_H__
#define __ABSTRACT_FACTORY_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Provide an interface for creating FAMILIES of related or dependent objects without specifying their concrete classes.
	/*
	The abstract factory pattern provides a way to encapsulate a group of individual factories that have a common 
	theme without specifying their concrete classes.[1] In normal usage, the client software creates a concrete 
	implementation of the abstract factory and then uses the generic interface of the factory to create the 
	concrete objects that are part of the theme. The client does not know (or care) which concrete objects it 
	gets from each of these internal factories, since it uses only the generic interfaces of their products.[1] 

	This pattern separates the details of implementation of a set of objects from their general usage and 
	relies on object composition, as object creation is implemented in methods exposed in the factory interface.[2]
	*/

	class Window {
	protected:

		int width;
		int height;

		std::string toolkit;
		std::string type;
 
		Window(std::string usedToolkit, std::string windowType)
			: toolkit(usedToolkit), type(windowType)
		{}
 
	public:

		std::string getToolkit()	{ return toolkit;	}
		std::string getType()		{ return type;		}

		void Free() { delete this; }
	};
 
	class GtkFooWindow : public Window {
	public:
		GtkFooWindow()
			: Window("Gtk", "FooWindow")
		{}
	};
 
	class GtkGooWindow : public Window {
	public:
		GtkGooWindow()
			: Window("Gtk", "GooWindow")
		{}
	};
 
	class QtFooWindow : public Window {
	public:
		QtFooWindow()
			: Window("Qt", "FooWindow")
		{}
	};
 
	class QtGooWindow : public Window {
	public:
		QtGooWindow()
		: Window("Qt", "GooWindow")
		{}
	};
 
	/* This is the abstract factory. */
	class UIFactory {
	public:

		virtual Window* getFooWindow() = 0;
		virtual Window* getGooWindow() = 0;
	};
 
	/* Factory for Gtk toolkit */
	class GtkUIFactory : public UIFactory {
	public:

		Window* getFooWindow()
		{
			return new GtkFooWindow();
		}
 
		Window* getGooWindow()
		{
			return new GtkGooWindow();
		}
	};
 
	/* Factory for Qt toolkit */
	class QtUIFactory : public UIFactory {
	public:

		Window* getFooWindow()
		{
			return new QtFooWindow();
		}

		Window* getGooWindow()
		{
			return new QtGooWindow();
		}
	};
}

#endif