
#ifndef __FACADE_H__
#define __FACADE_H__

#define BOOT_ADDRESS	0x0000abcd
#define BOOT_SECTOR		0x0000ccff
#define SECTOR_SIZE		0x000000ff

#include "DesignPattern.h"

namespace DesignPattern
{
	// Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface 
	// that makes the subsystem easier to use.
	/*
	The facade pattern (or façade pattern) is a software design pattern commonly used with object-oriented programming. 
	The name is by analogy to an architectural facade.

	A facade is an object that provides a simplified interface to a larger body of code, such as a class library. 
	A facade can:

	- make a software library easier to use, understand and test, since the facade has convenient methods for common tasks;
	- make the library more readable, for the same reason;
	- reduce dependencies of outside code on the inner workings of a library, since most code uses the facade, thus allowing more flexibility in developing the system;
	- wrap a poorly designed collection of APIs with a single well-designed API (as per task needs).
	*/

	/* Complex parts */
	class CPU {
	public:
		void freeze() { }
		void jump(long position) { }
		void execute() { }
	};

	class Memory {
	public:
		void load(long position, char* data) { }
	};

	class HardDrive {
	public:
		char* read(long lba, int size) { return NULL; }
	};

	/* Facade */
	class ComputerFacade {
	private:
		CPU processor;
		Memory ram;
		HardDrive hd;

	public:

		void start() 
		{
			processor.freeze();
			ram.load(BOOT_ADDRESS, hd.read(BOOT_SECTOR, SECTOR_SIZE));
			processor.jump(BOOT_ADDRESS);
			processor.execute();
		}
	};
}

#endif