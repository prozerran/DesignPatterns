
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Provide a way to access the elements of an aggregate object sequentially without exposing its underlying 
	// representation.
	/*
	In object-oriented programming, the iterator pattern is a design pattern in which an iterator is used to 
	traverse a container and access the container's elements. The iterator pattern decouples algorithms from containers; 
	in some cases, algorithms are necessarily container-specific and thus cannot be decoupled.
	*/

	class IIterator {
	public:
		virtual std::string FirstItem() = 0;
		virtual std::string NextItem() = 0;
		virtual std::string CurrentItem() = 0;
		virtual bool IsDone() = 0;		
	};

	class IAggregate {
	public:

		virtual IIterator* GetIterator() = 0;
		virtual std::string& operator[](int itemIndex) = 0;
		virtual int Count() = 0;
	};

	class MyIterator : public IIterator {
	public:

		MyIterator(IAggregate *aggregate)
			: currentIndex_(0)
			, aggregate_(aggregate)
		{}

		std::string FirstItem()
		{
			currentIndex_ = 0;
			return (*aggregate_)[currentIndex_];
		}

		std::string NextItem()
		{
			currentIndex_ += 1;

			if (IsDone() == false)
				return (*aggregate_)[currentIndex_];
			else
				return "";
		}

		std::string CurrentItem()
		{
			return (*aggregate_)[currentIndex_];
		}

		bool IsDone()
		{
			if (currentIndex_ < aggregate_->Count())
				return false;
			return true;
		}

	private:
		IAggregate *aggregate_;
		int currentIndex_;
	};

	class MyAggregate : public IAggregate {
	public:

		MyAggregate() {}

		//Helper function to populate the collection
		void AddValue(std::string value)
		{
			values_.push_back(value);
		}

		IIterator* GetIterator()
		{
			return new MyIterator(this);
		}

		std::string& operator[](int itemIndex)
		{
			return values_[itemIndex];
		}	

		int Count()
		{
			return values_.size();
		}

	private:
		std::vector<std::string> values_;
	};
}

#endif