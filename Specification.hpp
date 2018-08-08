
#ifndef __SPECIFICATION_H__
#define __SPECIFICATION_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Recombinable business logic in a Boolean fashion
	/*
	In computer programming, the specification pattern is a particular software design pattern, whereby business
	rules can be recombined by chaining the business rules together using boolean logic.
	*/
	class ISpecification {
	public:

		virtual bool IsSatisfiedBy(void* candidate) = 0;
		virtual ISpecification* And(ISpecification* other) = 0;
		virtual ISpecification* Or(ISpecification* other) = 0;
		virtual ISpecification* Not() = 0;
	};

	class CompositeSpecification : public ISpecification {
	public:

		bool IsSatisfiedBy(void* candidate) { return false; }
		ISpecification* And(ISpecification* other);
		ISpecification* Or(ISpecification* other);
		ISpecification* Not();
	};

	class AndSpecification : public CompositeSpecification {
	public:

		AndSpecification(ISpecification* x, ISpecification* y) 
			: One(x), Other(y)
		{}

		bool IsSatisfiedBy(void* candidate) 
		{
			return One->IsSatisfiedBy(candidate) && Other->IsSatisfiedBy(candidate);
		}

	private:
		ISpecification* One;
		ISpecification* Other;
	};

	class OrSpecification : public CompositeSpecification {
	public:

		OrSpecification(ISpecification* x, ISpecification* y) 
			: One(x), Other(y)
		{}

		bool IsSatisfiedBy(void* candidate) 
		{
			return One->IsSatisfiedBy(candidate) || Other->IsSatisfiedBy(candidate);
		}

	private:
		ISpecification* One;
		ISpecification* Other;
	};

	class NotSpecification : public CompositeSpecification {
	public:

		NotSpecification(ISpecification* x) 
			: Wrapped(x)
		{}

		bool IsSatisfiedBy(void* candidate) 
		{
			return !Wrapped->IsSatisfiedBy(candidate);
		}

	private:
		ISpecification* Wrapped;
	};

	ISpecification* CompositeSpecification::And(ISpecification* other)	{ return new AndSpecification(this, other); }
	ISpecification* CompositeSpecification::Or(ISpecification* other)	{ return new OrSpecification(this, other);	}
	ISpecification* CompositeSpecification::Not()						{ return new NotSpecification(this);		}
}

#endif