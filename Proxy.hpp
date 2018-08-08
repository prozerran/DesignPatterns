
#ifndef __PROXY_H__
#define __PROXY_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Provide a surrogate or placeholder for another object to control access to it.
	/*
	A proxy, in its most general form, is a class functioning as an interface to something else. The proxy could 
	interface to anything: a network connection, a large object in memory, a file, or some other resource that
	is expensive or impossible to duplicate.
	*/

	class Image {
	public:

		virtual ~Image() {}
		virtual void displayImage() = 0;
	};
 
	//on System A 
	class RealImage : public Image {
	public:
		RealImage(const std::string FILENAME) 
		{ 
			filename = FILENAME;  //TO DO real image can be a singleton
			loadImageFromDisk();
		}
 
		void displayImage() { 
			std::cout << "\tDisplaying " + filename;
			std::cout << "\n";
		}

	private:
		std::string filename;

		void loadImageFromDisk() {
			std::cout << "\tLoading " + filename;
			std::cout << "\n";
		}
	};
 
	//on System B 
	class ProxyImage : public Image {
	public:

		ProxyImage(const std::string FILENAME) 
			: image(NULL)
		{ 
			filename = FILENAME; 
		}

		~ProxyImage() { delete image; }
 
		void displayImage() {
			if (image == NULL) 
			{
			   image = new RealImage(filename);  //RealImage should be a singleton
			} 
			image->displayImage();
		}

	private:
		RealImage* image;
		std::string filename;
	};
}

#endif