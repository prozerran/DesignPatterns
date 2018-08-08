// TestPattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// design pattern headers
#include "LazyInitialization.hpp"		// Includes simple Multiton
#include "Monostate.hpp"				// Variation of Singleton
#include "Singleton.hpp"				// Singleton
#include "Multiton.hpp"					// Extended/Template Multiton
#include "RAII.hpp"						// Resource Acquisition Is Initialization
#include "Factory.hpp"					// Factory
#include "AbstractFactory.hpp"			// Abstract Factory
#include "Prototype.hpp"				// Prototype
#include "Builder.hpp"					// Builder
#include "ObjectPool.hpp"				// Object Pool
#include "Adapter.hpp"					// Similar to Wrapper
#include "Bridge.hpp"					// Bridge
#include "Composite.hpp"				// Composite
#include "Decorator.hpp"				// Similar to Wrapper
#include "Facade.hpp"					// Similar to Wrapper
#include "FlyWeight.hpp"				// FlyWeight
#include "Proxy.hpp"					// Proxy
#include "Iterator.hpp"					// Iterator
#include "ChainResponsibility.hpp"		// Chain of Responsibility
#include "Command.hpp"					// Chain of Command
#include "Interpreter.hpp"				// Simple Interpreter only
#include "Mediator.hpp"					// Mediator
#include "Memento.hpp"					// Memento
#include "NullObject.hpp"				// Null Object
#include "PublisherSubscriber.hpp"		// Similar to Observer
#include "RegisterCallback.hpp"			// Sets a Callback method
#include "Servant.hpp"					// Utility class
#include "Specification.hpp"			// Specification
#include "State.hpp"					// State
#include "Strategy.hpp"					// Policy
#include "TemplateMethod.hpp"			// Template Method
#include "Visitor.hpp"					// Visitor
#include "ScopedLock.hpp"				// Lock
#include "DoubleCheckLocking.hpp"		// Double Check Locking
#include "SingleInstance.hpp"			// Limit Single Instance
#include "Thread.hpp"					// Threading
#include "ThreadPool.hpp"				// Thread Pool

using namespace DesignPattern;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("%-30s %s\n", "Design Patterns", "Output");
	printf("=====================================\n");

	/* *************************************** */
	//
	// Example LazyInitialization
	//
	/* *************************************** */

	Fruit::getFruit("Banana");	//Fruit::printCurrentTypes();
	Fruit::getFruit("Apple");	//Fruit::printCurrentTypes();
	// returns pre-existing instance from first time Fruit with "Banana" was created
	Fruit::getFruit("Banana");	//Fruit::printCurrentTypes();
	Fruit::delAll();
	printf("%-30s %s\n", "LazyInitialization", "OK");

	/* *************************************** */
	//
	// Example Monostate
	//
	/* *************************************** */

	Monostate mon;
	mon.SetString("OK");
	printf("%-30s %s\n", "Monostate", mon.InvokeMethod());

	/* *************************************** */
	//
	// Example Singleton
	//
	/* *************************************** */

	Singleton& sig = Singleton::Instance();
	printf("%-30s %s\n", "Singleton", sig.InvokeMethod());

	/* *************************************** */
	//
	// Example Multiton
	//
	/* *************************************** */

	class Foo : public Multiton<Foo> {};	// you may declare your own multiton!
	Foo& foo1 = Foo::getRef("foobar");
	Foo* foo2 = Foo::getPtr("foobar");
	Foo::destroy();
	printf("%-30s %s\n", "Multiton", "OK");

	/* *************************************** */
	//
	// Example Factory
	//
	/* *************************************** */

	IEmployee *emp = IEmployee::CreateEmployee(IEmployee::MANAGER);
	emp->Free();
	printf("%-30s %s\n", "Factory", "OK");

	/* *************************************** */
	//
	// Example Abstract Factory
	//
	/* *************************************** */

	UIFactory* ui = NULL;
	if (NULL)
		ui = new GtkUIFactory();
	else
		ui = new QtUIFactory();

	/* Use the factory to build interface. */
	Window* foo = ui->getFooWindow();
	Window* goo = ui->getGooWindow();
	/* See what have we recieved. */
	//std::cout << foo->getToolkit() << ":" << foo->getType() << std::endl;
	//std::cout << goo->getToolkit() << ":" << goo->getType() << std::endl;
	foo->Free();
	goo->Free();
	printf("%-30s %s\n", "Abstract Factory", "OK");	

	/* *************************************** */
	//
	// Example Prototype
	//
	/* *************************************** */

	ObjectFactory::Initialize();
	Prototype* object = NULL;
	/* All the object were created by cloning the prototypes. */
	/*
	object = ObjectFactory::getType1Value1();
	std::cout << object->getType() << ": " << object->getValue() << std::endl;
	object->Free();
	
	object = ObjectFactory::getType1Value2();
	std::cout << object->getType() << ": " << object->getValue() << std::endl;
	object->Free();

	object = ObjectFactory::getType2Value1();
	std::cout << object->getType() << ": " << object->getValue() << std::endl;
	object->Free();
	*/
	object = ObjectFactory::getType2Value2();
	//std::cout << object->getType() << ": " << object->getValue() << std::endl;
	object->Free();
	ObjectFactory::Free();
	printf("%-30s %s\n", "Prototype", "OK");	

	/* *************************************** */
	//
	// Example Builder
	//
	/* *************************************** */

	Car* car;						// Final product
	Director director;				// A director who controls the process
	JeepBuilder jeepBuilder;		// Concrete builders
	NissanBuilder nissanBuilder;	// Concrete builders
	
	/* Build a Jeep */
	director.setBuilder(&jeepBuilder); // using JeepBuilder instance
	car = director.getCar();
	//car->specifications();
	car->free();

	/* Build a Nissan */
	director.setBuilder(&nissanBuilder); // using NissanBuilder instance
	car = director.getCar();
	//car->specifications();
	car->free();
	printf("%-30s %s\n", "Builder", "OK");	

	/* *************************************** */
	//
	// Example Object Pool
	//
	/* *************************************** */

	ObjectPool& pool = ObjectPool::getInstance();

	/* Resources will be created. */
	Resource* one = pool.getResource();
	one->setValue(10);
	//std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;

	Resource* two = pool.getResource();
	two->setValue(20);
	//std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	pool.returnResource(one);
	pool.returnResource(two);
	/* Resources will be reused.
	* Notice that the value of both resources were reset back to zero.
	*/
	one = pool.getResource();
	//std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
	two = pool.getResource();
	//std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	pool.returnResource(one);
	pool.returnResource(two);
	printf("%-30s %s\n", "Object Pool", "OK");	

	/* *************************************** */
	//
	// Example Adapter/Wrapper/Translator
	//
	/* *************************************** */

	Wrapper w;
	printf("%-30s %s\n", "Wrapper", w.InvokeMethod());

	/* *************************************** */
	//
	// Example Bridge
	//
	/* *************************************** */

	AbstractInterface *useCase = NULL;
	ImplementationInterface *osWindows = new Windows;
	ImplementationInterface *osLinux = new Linux;

	/* First case */
	useCase = new UseCase1(osWindows);
	//useCase->someFunctionality();
	delete useCase;

	useCase = new UseCase1(osLinux);
	//useCase->someFunctionality();
	delete useCase;

	/* Second case */
	useCase = new UseCase2(osWindows);
	//useCase->someFunctionality();
	delete useCase;

	useCase = new UseCase2(osLinux);
	//useCase->someFunctionality();
	delete useCase;
	printf("%-30s %s\n", "Bridge", "OK");

	/* *************************************** */
	//
	// Example Composite
	//
	/* *************************************** */

	Composite containers[4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			containers[i].add(new Leaf(i *3+j));

	for (int i = 1; i < 4; i++)
		containers[0].add(&(containers[i]));

	for (int i = 0; i < 4; i++)
	{
		//containers[i].traverse();
		//std::cout << std::endl;
	}
	printf("%-30s %s\n", "Composite", "OK");
	// free containers?!?

	/* *************************************** */
	//
	// Example Decorator
	//
	/* *************************************** */

	SimpleCoffee sc;
	//std::cout << "Cost: " << sc.getCost() << "; Ingredients: " << sc.getIngredients() << std::endl;

	MilkDecorator md(&sc);
	//std::cout << "Cost: " << md.getCost() << "; Ingredients: " << md.getIngredients() << std::endl;

	WhipDecorator wd(&sc);
	//std::cout << "Cost: " << wd.getCost() << "; Ingredients: " << wd.getIngredients() << std::endl;

	// Note that you can stack decorators:
	MilkDecorator md2(&wd);
	//std::cout << "Cost: " << md2.getCost() << "; Ingredients: " << md2.getIngredients() << std::endl;
	printf("%-30s %s\n", "Decorator", "OK");

	/* *************************************** */
	//
	// Example Facade
	//
	/* *************************************** */

	ComputerFacade computer;
	computer.start();
	printf("%-30s %s\n", "Facade", "OK");

	/* *************************************** */
	//
	// Example FlyWeight
	//
	/* *************************************** */

	for (int i = 0; i < Factory::X; ++i)
	{
		//for (int j = 0; j < Factory::Y; ++j)
		//	Factory::get_fly(i)->report(j);
		//std::cout << std::endl;
	}
	Factory::clean_up();
	printf("%-30s %s\n", "FlyWeight", "OK");

	/* *************************************** */
	//
	// Example Proxy
	//
	/* *************************************** */

	Image* image1 = new ProxyImage("HiRes_10MB_Photo1");
	Image* image2 = new ProxyImage("HiRes_10MB_Photo2");
	/*
	image1->displayImage(); // loading necessary
	image1->displayImage(); // loading unnecessary
	image2->displayImage(); // loading necessary
	image2->displayImage(); // loading unnecessary
	image1->displayImage(); // loading unnecessary
	*/
	delete image1;
	delete image2;
	printf("%-30s %s\n", "Proxy", "OK");

	/* *************************************** */
	//
	// Example Iterator
	//
	/* *************************************** */

	MyAggregate aggr;
	aggr.AddValue("1");
	aggr.AddValue("2");
	aggr.AddValue("3");
	aggr.AddValue("4");
	aggr.AddValue("5");
	aggr.AddValue("6");
	aggr.AddValue("7");
	aggr.AddValue("8");
	aggr.AddValue("9");
	aggr.AddValue("10");

	IIterator *iter = aggr.GetIterator();
	for (std::string s = iter->FirstItem(); iter->IsDone() == false;  s = iter->NextItem() )
	;//	std::cout << s << std::endl;
	printf("%-30s %s\n", "Iterator", "OK");
	delete iter;

	/* *************************************** */
	//
	// Example Chain of Responsibility
	//
	/* *************************************** */

	srand((unsigned int) time(NULL));
	Handler1 h1;	// root
	Handler2 h2;
	Handler3 h3;
	h1.add(&h2);
	h1.add(&h3);
	h3.setNext(&h1);
	for (int i = 1; i < 10; i++)
	{
		//h1.handle(i);
		//std::cout << '\n';
	}
	printf("%-30s %s\n", "Chain of Responsibility", "OK");

	/* *************************************** */
	//
	// Example Command
	//
	/* *************************************** */

	// Fred will "execute" Barney which will result in a call to passOn()
	// Barney will "execute" Betty which will result in a call to gossip()
	// Betty will "execute" Wilma which will result in a call to listen()
	Person wilma("Wilma", Command());
	// 2. Instantiate an object for each "callback"
	// 3. Pass each object to its future "sender"
	Person betty("Betty", Command(&wilma, &Person::listen));
	Person barney("Barney", Command(&betty, &Person::gossip));
	Person fred("Fred", Command(&barney, &Person::passOn));
	//fred.talk();	// invoke all!
	printf("%-30s %s\n", "Command", "OK");

	/* *************************************** */
	//
	// Example Interpreter
	//
	/* *************************************** */

	//InterpretMethod("h w!n");
	printf("%-30s %s\n", "Interpreter", "OK");

	/* *************************************** */
	//
	// Example Mediator
	//
	/* *************************************** */
	
	CPrinter printer;  
	CMessage message;  
	//MediatorMethod(CMediatorPattern(printer,message));
	printf("%-30s %s\n", "Mediator", "OK");

	/* *************************************** */
	//
	// Example Memento
	//
	/* *************************************** */

	// Caretaker
	Originator *obj = new Originator(100,50);
	Memento *snapshot = new Memento;

	// before snapshot
	//std::cout << obj->getMemberA() << " " <<  obj->getMemberB() << std::endl;
	obj->createMemento(&snapshot);

	// change value
	obj->setMemberA(7);
	obj->setMemberB(45);
	//std::cout << obj->getMemberA() << " " <<  obj->getMemberB() << std::endl;
	obj->restoreMemento(snapshot);
	delete snapshot;

	// restore snapshot
	//std::cout << obj->getMemberA() << " " <<  obj->getMemberB() << std::endl;
	delete obj;
	printf("%-30s %s\n", "Memento", "OK");

	/* *************************************** */
	//
	// Example Null Object
	//
	/* *************************************** */

	IAnimal* animal = NULL;
	int input = 1;

	if (1)
		animal = new Dog();
	else if (2)
		animal = new Cat();
	else
		animal = new Null_Animal();		// Create NULL Object so we don't have to test for NULL
	
	//animal->make_sound();
	printf("%-30s %s\n", "Null Object", "OK");

	/* *************************************** */
	//
	// Example Publisher-Subscriber
	//
	/* *************************************** */

	Publisher p;
	MySubscriber mys;

	p.subscribe(&mys);
	//p.notify("Hello World!"); // calls MySubscriber.update
	printf("%-30s %s\n", "Publisher-Subscriber", "OK");

	/* *************************************** */
	//
	// Example Register Callback
	//
	/* *************************************** */

	ObjectManager obm;
	//obm.RegisterCallback(MyCallbackMethod, "Hello World\n");
	//obm.NotifyCallback();

	MyObject myobj;
	obm.RegisterCallback(&MyObject::MyCallbackMethod, &myobj);
	//obm.NotifyCallback();
	printf("%-30s %s\n", "Register Callback", "OK");

	/* *************************************** */
	//
	// Example Servant
	//
	/* *************************************** */

	VoteServant vs;
	VoteAble* t1 = new TeamOne();
	vs.addTotalScore(t1, 10);
	vs.addScore(t1, 3);
	printf("%-30s %s\n", "Servant", "OK");
	delete t1;

	/* *************************************** */
	//
	// Example Specification
	//
	/* *************************************** */

	ISpecification* pSpec = new CompositeSpecification();
	delete pSpec;
	printf("%-30s %s\n", "Specification", "TODO");

	/* *************************************** */
	//
	// Example State
	//
	/* *************************************** */
	StateContext stc;
	/*
	stc.writeName("Monday");
	stc.writeName("Tuesday");
	stc.writeName("Wednesday");
	stc.writeName("Thursday");
	stc.writeName("Friday");
	stc.writeName("Saturday");
	stc.writeName("Sunday");
	*/
	printf("%-30s %s\n", "State", "LEAK");

	/* *************************************** */
	//
	// Example Strategy
	//
	/* *************************************** */

	Context* con = NULL;
	Add a; Subtract s; Multiply m;

	// Three contexts following different strategies
	if (1)
		con = new Context(&a);
	else if (2)
		con = new Context(&s);
	else
		con = new Context(&m);

	// polymorphism
	int res = con->executeStrategy(3,4);
	delete con;

	//std::cout << "Result : " << res << std::endl;
	printf("%-30s %s\n", "Strategy", "OK");

	/* *************************************** */
	//
	// Example Template Method
	//
	/* *************************************** */

	// Top dog way to instantiate object and store by reference
	TMBase *array[] = { new One(), new Two() };

	for (int i = 0; i < SIZEOF_ARRAY(array); i++)
	{
		//array[i]->execute();
		//std::cout << std::endl;
		delete array[i];
	}
	printf("%-30s %s\n", "Template Method", "OK");
	
	/* *************************************** */
	//
	// Example Visitor
	//
	/* *************************************** */

	Element *list[] = { new This(), new That(), new TheOther() };

	UpVisitor up;					// 4. Client creates
	DownVisitor down;				// "visitor" objects
	/*
	FOR_EACH (Element*, e, list)
		e->accept(up);

	FOR_EACH (Element*, e, list)
		e->accept(down);
	*/
	FOR_EACH (Element*, e, list)
		delete e;

	printf("%-30s %s\n", "Visitor", "OK");

	/* *************************************** */
	//
	// Example ScopedLock
	//
	/* *************************************** */

	// locks the current scope for mutual exclusive access
	{
		mutex_t my_mtx;
		ScopedLock lock(my_mtx);
		printf("%-30s %s\n", "ScopedLock", "OK");
	}

	/* *************************************** */
	//
	// Example Double Check Locking
	//
	/* *************************************** */

	DoubleCheckLocking* dcl = DoubleCheckLocking::Instance();
	printf("%-30s %s\n", "Double Check Locking", dcl->InvokeMethod());

	/* *************************************** */
	//
	// Example Limit Single Instance
	//
	/* *************************************** */

	// The one and only SingleInstance object.
	// Change what is passed to constructor. GUIDGEN Tool may be of help.
	SingleInstance sIntObj(TEXT("Global\\{719967F0-DCC6-49b5-9C61-DE91175C3187}"));

	if (sIntObj.IsAnotherInstanceRunning())
		return -1;

	printf("%-30s %s\n", "Limit Single Instance", "OK");

	/* *************************************** */
	//
	// Example Threading
	//
	/* *************************************** */

	MyThread my_thr;
	my_thr.Start();
	my_thr.Join();
	printf("%-30s %s\n", "Threading", "OK");

	/* *************************************** */
	//
	// Example Thread Pool
	// Sample shows running 10 task on 3 threads
	//
	/* *************************************** */

	ThreadPool thr_pool(3);		// N-threads run simultaneously!

	// simulate add some task into our queue to be executed
	for (int i = 0; i < 10; i++)
	{
		thr_pool.AddTask((Task) i);
	}

	thr_pool.ProcessPool();
	printf("%-30s %s\n", "Thread Pool", "OK");

	return 0;
}

