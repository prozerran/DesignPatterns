// TestPattern_gTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "DesignPatterns.h"

namespace DesignPattern
{
	TEST(Creational, LazyInitialization) 
	{
		Fruit::getFruit("Banana");	Fruit::printCurrentTypes();
		Fruit::getFruit("Apple");	Fruit::printCurrentTypes();
		Fruit::getFruit("Banana");	Fruit::printCurrentTypes();
		Fruit::delAll();
	}

	TEST(Creational, Monostate) 
	{
		Monostate mon;
		mon.SetString("OK");
		mon.InvokeMethod();
	}

	TEST(Creational, Singleton) 
	{
		Singleton& sig = Singleton::Instance();
		sig.InvokeMethod();
	}

	TEST(Creational, Multiton) 
	{
		class Foo : public Multiton<Foo> {};	// you may declare your own multiton!
		Foo& foo1 = Foo::getRef("foobar");
		Foo* foo2 = Foo::getPtr("foobar");
		Foo::destroy();
	}

	TEST(Creational, Factory) 
	{
		IEmployee *emp = IEmployee::CreateEmployee(IEmployee::MANAGER);
		ASSERT_TRUE(emp != NULL);
		emp->Free();
	}

	TEST(Creational, AbstractFactory) 
	{
		UIFactory* ui = NULL;
		if (NULL)
			ui = new GtkUIFactory();
		else
			ui = new QtUIFactory();

		Window* foo = ui->getFooWindow();
		Window* goo = ui->getGooWindow();

		ASSERT_TRUE(foo != NULL);
		ASSERT_TRUE(goo != NULL);

		EXPECT_EQ("Qt", foo->getToolkit());	EXPECT_EQ("FooWindow", foo->getType());
		EXPECT_EQ("Qt", goo->getToolkit());	EXPECT_EQ("GooWindow", goo->getType());

		foo->Free();
		goo->Free();
	}

	TEST(Creational, Prototype) 
	{
		ObjectFactory::Initialize();
		Prototype* object = NULL;

		/* All the object were created by cloning the prototypes. */
		object = ObjectFactory::getType1Value1();
		EXPECT_EQ("Type1", object->getType());	EXPECT_EQ(1, object->getValue());
		object->Free();
	
		object = ObjectFactory::getType1Value2();
		EXPECT_EQ("Type1", object->getType());	EXPECT_EQ(2, object->getValue());
		object->Free();

		object = ObjectFactory::getType2Value1();
		EXPECT_EQ("Type2", object->getType());	EXPECT_EQ(1, object->getValue());
		object->Free();

		object = ObjectFactory::getType2Value2();
		EXPECT_EQ("Type2", object->getType());	EXPECT_EQ(2, object->getValue());
		object->Free();
		ObjectFactory::Free();
	}

	TEST(Creational, Builder) 
	{
		Car* car;						// Final product
		Director director;				// A director who controls the process
		JeepBuilder jeepBuilder;		// Concrete builders
		NissanBuilder nissanBuilder;	// Concrete builders

		/* Build a Jeep */
		director.setBuilder(&jeepBuilder); // using JeepBuilder instance
		car = director.getCar();
		ASSERT_TRUE(car != NULL);
		car->specifications();
		car->free();

		/* Build a Nissan */
		director.setBuilder(&nissanBuilder); // using NissanBuilder instance
		car = director.getCar();
		ASSERT_TRUE(car != NULL);
		car->specifications();
		car->free();
	}

	TEST(Creational, ObjectPool) 
	{
		ObjectPool& pool = ObjectPool::getInstance();

		/* Resources will be created. */
		Resource* one = pool.getResource();
		ASSERT_TRUE(one != NULL);
		one->setValue(10);
		EXPECT_EQ(10, one->getValue());

		Resource* two = pool.getResource();
		ASSERT_TRUE(two != NULL);
		two->setValue(20);
		EXPECT_EQ(20, two->getValue());

		pool.returnResource(one);
		pool.returnResource(two);

		/* Resources will be reused.
		* Notice that the value of both resources were reset back to zero.
		*/
		one = pool.getResource();
		EXPECT_EQ(0, one->getValue());

		two = pool.getResource();
		EXPECT_EQ(0, two->getValue());

		pool.returnResource(one);
		pool.returnResource(two);
	}

	TEST(Structural, Adapter) 
	{
		Wrapper w;
		w.InvokeMethod();
	}

	TEST(Structural, Bridge) 
	{
		AbstractInterface *useCase = NULL;
		ImplementationInterface *osWindows = new Windows;
		ImplementationInterface *osLinux = new Linux;

		ASSERT_TRUE(osWindows != NULL);
		ASSERT_TRUE(osLinux != NULL);

		/* First case */
		useCase = new UseCase1(osWindows);
		ASSERT_TRUE(useCase != NULL);
		useCase->someFunctionality();
		delete useCase;

		useCase = new UseCase1(osLinux);
		ASSERT_TRUE(useCase != NULL);
		useCase->someFunctionality();
		delete useCase;

		/* Second case */
		useCase = new UseCase2(osWindows);
		ASSERT_TRUE(useCase != NULL);
		useCase->someFunctionality();
		delete useCase;

		useCase = new UseCase2(osLinux);
		ASSERT_TRUE(useCase != NULL);
		useCase->someFunctionality();
		delete useCase;
	}

	TEST(Structural, Composite) 
	{
		Composite containers[4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				containers[i].add(new Leaf(i *3+j));

		for (int i = 1; i < 4; i++)
			containers[0].add(&(containers[i]));

		for (int i = 0; i < 4; i++)
		{
			containers[i].traverse();
			std::cout << std::endl;
		}
		// free containers?!?
	}

	TEST(Structural, Decorator) 
	{
		SimpleCoffee sc;
		EXPECT_EQ(1, sc.getCost());	EXPECT_EQ("Coffee", sc.getIngredients());

		MilkDecorator md(&sc);
		EXPECT_EQ(1.5, md.getCost());	EXPECT_EQ("Coffee, Milk", md.getIngredients());

		WhipDecorator wd(&sc);
		EXPECT_EQ(1.7, wd.getCost());	EXPECT_EQ("Coffee, Whip", wd.getIngredients());

		// Note that you can stack decorators:
		MilkDecorator md2(&wd);
		EXPECT_EQ(2.2, md2.getCost());	EXPECT_EQ("Coffee, Whip, Milk", md2.getIngredients());
	}

	TEST(Structural, Facade) 
	{
		ComputerFacade computer;
		computer.start();
	}

	TEST(Structural, FlyWeight) 
	{
		for (int i = 0; i < Factory::X; ++i)
		{
			for (int j = 0; j < Factory::Y; ++j)			
				Factory::get_fly(i)->report(j);
			
			std::cout << std::endl;
		}
		std::cout << "\t";
		Factory::clean_up();
		std::cout << std::endl;
	}

	TEST(Structural, Proxy) 
	{
		Image* image1 = new ProxyImage("HiRes_10MB_Photo1");
		Image* image2 = new ProxyImage("HiRes_10MB_Photo2");

		ASSERT_TRUE(image1 != NULL);
		ASSERT_TRUE(image2 != NULL);

		image1->displayImage(); // loading necessary
		image1->displayImage(); // loading unnecessary
		image2->displayImage(); // loading necessary
		image2->displayImage(); // loading unnecessary
		image1->displayImage(); // loading unnecessary

		delete image1;
		delete image2;
	}

	TEST(Behavioral, Iterator) 
	{
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
		ASSERT_TRUE(iter != NULL);

		for (std::string s = iter->FirstItem(); iter->IsDone() == false;  s = iter->NextItem() )
			std::cout << "\t" << s << std::endl;

		delete iter;
	}

	TEST(Behavioral, ChainOfResponsibility) 
	{
		srand((unsigned int) time(NULL));
		Handler1 h1;	// root
		Handler2 h2;
		Handler3 h3;
		h1.add(&h2);
		h1.add(&h3);
		h3.setNext(&h1);
		for (int i = 1; i < 10; i++)
		{
			std::cout << '\t';
			h1.handle(i);
			std::cout << '\n';
		}
	}

	TEST(Behavioral, Command) 
	{
		// Fred will "execute" Barney which will result in a call to passOn()
		// Barney will "execute" Betty which will result in a call to gossip()
		// Betty will "execute" Wilma which will result in a call to listen()
		Person wilma("Wilma", Command());
		// 2. Instantiate an object for each "callback"
		// 3. Pass each object to its future "sender"
		Person betty("Betty", Command(&wilma, &Person::listen));
		Person barney("Barney", Command(&betty, &Person::gossip));
		Person fred("Fred", Command(&barney, &Person::passOn));
		fred.talk();	// invoke all!
	}

	TEST(Behavioral, Interpreter) 
	{
		InterpretMethod("h w!n");
	}

	TEST(Behavioral, Mediator) 
	{
		CPrinter printer;  
		CMessage message;  
		MediatorMethod(CMediatorPattern(printer,message));
	}

	TEST(Behavioral, Memento) 
	{
		// Caretaker
		Originator *obj = new Originator(100,50);
		Memento *snapshot = new Memento;

		ASSERT_TRUE(obj != NULL);
		ASSERT_TRUE(snapshot != NULL);

		// before snapshot
		EXPECT_EQ(100, obj->getMemberA());	EXPECT_EQ(50, obj->getMemberB());
		obj->createMemento(&snapshot);

		// change value
		obj->setMemberA(7);
		obj->setMemberB(45);
		EXPECT_EQ(7, obj->getMemberA());	EXPECT_EQ(45, obj->getMemberB());
		obj->restoreMemento(snapshot);
		delete snapshot;

		// restore snapshot
		EXPECT_EQ(100, obj->getMemberA());	EXPECT_EQ(50, obj->getMemberB());
		delete obj;
	}

	TEST(Behavioral, NullObject) 
	{
		IAnimal* animal = NULL;
		int input = 1;

		if (1)
			animal = new Dog();
		else if (2)
			animal = new Cat();
		else
			animal = new Null_Animal();		// Create NULL Object so we dont have to test for NULL

		ASSERT_TRUE(animal != NULL);
		animal->make_sound();
	}

	TEST(Behavioral, PublisherSubsriber) 
	{
		Publisher p;
		MySubscriber mys;

		p.subscribe(&mys);
		p.notify("Hello World!"); // calls MySubscriber.update
	}

	TEST(Behavioral, RegisterCallback) 
	{
		ObjectManager obm;
		obm.RegisterCallback(MyCallbackMethod, "Hello World\n");
		obm.NotifyCallback();

		MyObject myobj;
		obm.RegisterCallback(&MyObject::MyCallbackMethod, &myobj);
		obm.NotifyCallback();
	}

	TEST(Behavioral, Servant) 
	{
		VoteServant vs;
		VoteAble* t1 = new TeamOne();
		ASSERT_TRUE(t1 != NULL);

		vs.addTotalScore(t1, 10);
		vs.addScore(t1, 3);
		delete t1;
	}

	TEST(Behavioral, Specification) 
	{
		ISpecification* pSpec = new CompositeSpecification();
		ASSERT_TRUE(pSpec != NULL);
		delete pSpec;
	}

	TEST(Behavioral, State) 
	{
		StateContext stc;
		stc.writeName("Monday");
		stc.writeName("Tuesday");
		stc.writeName("Wednesday");
		stc.writeName("Thursday");
		stc.writeName("Friday");
		stc.writeName("Saturday");
		stc.writeName("Sunday");
	}

	TEST(Behavioral, Strategy) 
	{
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
		ASSERT_TRUE(con != NULL);
		int res = con->executeStrategy(3,4);
		delete con;

		EXPECT_EQ(7, res);
	}
	
	TEST(Behavioral, TemplateMethod) 
	{
		// Top dog way to instantiate object and store by reference
		TMBase *array[] = { new One(), new Two() };
		ASSERT_TRUE(array != NULL);

		for (int i = 0; i < SIZEOF_ARRAY(array); i++)
		{
			ASSERT_TRUE(array[i] != NULL);
			array[i]->execute();
			delete array[i];
		}
	}

	TEST(Behavioral, Visitor) 
	{
		Element *list[] = { new This(), new That(), new TheOther() };
		ASSERT_TRUE(list != NULL);

		UpVisitor up;					// 4. Client creates
		DownVisitor down;				// "visitor" objects

		FOR_EACH (Element*, e, list)
			e->accept(up);

		FOR_EACH (Element*, e, list)
			e->accept(down);

		FOR_EACH (Element*, e, list)
			delete e;
	}

	TEST(Concurrency, ScopedLock) 
	{
		// locks the current scope for mutual exclusive access
		{
			mutex_t my_mtx;
			ScopedLock lock(my_mtx);
		}
	}

	TEST(Concurrency, DoubleCheckLocking) 
	{
		DoubleCheckLocking* dcl = DoubleCheckLocking::Instance();
		ASSERT_TRUE(dcl != NULL);
		dcl->InvokeMethod();
	}

	TEST(Concurrency, LimitSingleInstance) 
	{
		// The one and only SingleInstance object.
		// Change what is passed to constructor. GUIDGEN Tool may be of help.
		SingleInstance sIntObj(TEXT("Global\\{719967F0-DCC6-49b5-9C61-DE91175C3187}"));

		if (sIntObj.IsAnotherInstanceRunning())
			return;

		ASSERT_FALSE(sIntObj.IsAnotherInstanceRunning());
	}

	TEST(Concurrency, Threading) 
	{
		MyThread my_thr;
		my_thr.Start();
		my_thr.Join();
	}

	TEST(Concurrency, ThreadPool) 
	{
		ThreadPool thr_pool(3);		// n-threads run simultaneously!

		// simulate add some task into our queue to be executed
		for (int i = 0; i < 10; i++)
		{
			thr_pool.AddTask((Task) i);
		}
		thr_pool.ProcessPool();
	}

}  // namespace

/* ********************************************************************************* */
//
//						Google Main Test
//
// $ TestPattern_gTest.exe --gtest_filter=*.*
//
// Basics:			http://code.google.com/p/googletest/wiki/Primer
// Advanced Topics: http://code.google.com/p/googletest/wiki/AdvancedGuide
//
/* ********************************************************************************* */

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}