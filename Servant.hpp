
#ifndef __SERVANT_H__
#define __SERVANT_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Define common functionality for a group of classes	
	/*
	Servant is a design pattern used to offer some functionality to a group of classes without defining that
	functionality in each of them. A Servant is a class whose instance (or even just class) provides 
	methods that take care of a desired service, while objects for which (or with whom) the servant does something, 
	are taken as parameters.
	*/

	// Interface specifying what serviced classes needs to implement, to be
	// serviced by servant.
	class VoteAble {
	public:

		virtual void setTotalPoint(int tp) = 0;
		virtual int getTotalPoint() = 0;

	protected:
		// Total point of this project
		int p;
	};

	// Servant class, offering its functionality to classes implementing
	// VoteAble Interface
	class VoteServant {
	public:

		// Method, which will add total point to vote able classes.
		void addTotalScore(VoteAble* va, int tp) 
		{
			// the place to offer the functionality
			va->setTotalPoint(tp);
		}

		// Method, which will add totalpoint by score 
		void addScore(VoteAble* va, int score) 
		{
			// this is the place to offer the functionality
			score = score + va->getTotalPoint();
			va->setTotalPoint(score);
		}
	};
	
	// One of project classes
	class TeamOne : public VoteAble  {
	public:

		// Method, which sets point of project object
		void setTotalPoint(int p) { this->p = p; }

		// Method, which returns totalpoint of project object
		int getTotalPoint() { return p; }
	};

	// One of geometric classes
	class TeamTwo : public VoteAble {
	public:
		// Total point of this project	private TotalPoint p;

		// Method, which sets point of project object
		void setTotalPoint(int p)  { this->p = p; }

		// Method, which returns totalpoint of project object
		int getTotalPoint() { return this->p; }
	};
}

#endif