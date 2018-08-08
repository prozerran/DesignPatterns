
#ifndef __BUILDER_H__
#define __BUILDER_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Separate the construction of a complex object from its representation allowing 
	// the same construction process to create various representations.
	/*
	The builder pattern is an object creation software design pattern. Unlike the abstract factory pattern and the 
	factory method pattern whose intention is to enable polymorphism, the intention of the builder pattern is to find a 
	solution to the telescoping constructor anti-pattern. The telescoping constructor anti-pattern occurs when the 
	increase of object constructor parameter combination leads to an exponential list of constructors. Instead of using 
	numerous constructors, the builder pattern uses another object, a builder, that receives each initialization 
	parameter step by step and then returns the resulting constructed object at once.
	*/
	/* Car parts */
	class Wheel {
	public:
		int size;
	};

	class Engine {
	public:
		int horsepower;
	};

	class Body {
	public:
		std::string shape;
	};

	/* Final product -- a car */
	class Car {
	public:
		Wheel* wheels[4];
		Engine* engine;
		Body* body;

		void free()
		{
			if (body)		{ delete body;		body = NULL; }
			if (engine)		{ delete engine;	engine	= NULL; }
			if (wheels[0])	{ delete wheels[0];	wheels[0] = NULL; }
			if (wheels[1])	{ delete wheels[1];	wheels[1] = NULL; }
			if (wheels[2])	{ delete wheels[2];	wheels[2] = NULL; }
			if (wheels[3])	{ delete wheels[3];	wheels[3] = NULL; }
			delete this;
		}

		void specifications()
		{
			std::cout << "\tbody:" << body->shape << std::endl;
			std::cout << "\tengine horsepower:" << engine->horsepower << std::endl;
			std::cout << "\ttire size:" << wheels[0]->size << "'" << std::endl;
		}
	};

	/* Builder is responsible for constructing the smaller parts */
	class Builder {
	public:
		virtual Wheel* getWheel() = 0;
		virtual Engine* getEngine() = 0;
		virtual Body* getBody() = 0;
	};

	/* Concrete Builder for Jeep SUV cars */
	class JeepBuilder : public Builder {
	public:
		Wheel* getWheel()
		{
			Wheel* wheel = new Wheel();
			wheel->size = 22;
			return wheel;
		}

		Engine* getEngine()
		{
			Engine* engine = new Engine();
			engine->horsepower = 400;
			return engine;
		}

		Body* getBody()
		{
			Body* body = new Body();
			body->shape = "SUV";
			return body;
		}
	};

	/* Concrete builder for Nissan family cars */
	class NissanBuilder : public Builder {
	public:
		Wheel* getWheel()
		{
			Wheel* wheel = new Wheel();
			wheel->size = 16;
			return wheel;
		}

		Engine* getEngine()
		{
			Engine* engine = new Engine();
			engine->horsepower = 85;
			return engine;
		}

		Body* getBody()
		{
			Body* body = new Body();
			body->shape = "hatchback";
			return body;
		}
	};

	/* Director is responsible for the whole process */
	class Director {
	public:
		void setBuilder(Builder* newBuilder)
		{
			builder = newBuilder;
		}

		Car* getCar()
		{
			Car* car	= new Car();
			car->body	= builder->getBody();
			car->engine = builder->getEngine();

			car->wheels[0] = builder->getWheel();
			car->wheels[1] = builder->getWheel();
			car->wheels[2] = builder->getWheel();
			car->wheels[3] = builder->getWheel();

			return car;
		}

	private:

		Builder* builder;
	};
}

#endif