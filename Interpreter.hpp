
#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "DesignPattern.h"

namespace DesignPattern
{
	// Given a language, define a representation for its grammar along with an interpreter that uses the representation 
	// to interpret sentences in the language.
	/*
	In computer programming, the interpreter pattern is a design pattern that specifies how to evaluate sentences 
	in a language. The basic idea is to have a class for each symbol (terminal or nonterminal) in a specialized 
	computer language. The syntax tree of a sentence in the language is an instance of the composite pattern and 
	is used to evaluate (interpret) the sentence.[1]
	*/
	class CInterpreter {  
	public:  

		template<typename It>  
		void m_run(It from, It to)  
		{  
			std::cout << "\t";   

			for(It i=from; i!=to; ++i)  
			{  
				switch(*i)  
				{  
				case 'h':  
					std::cout << "Hello";    
					break;  
				case ' ':   
					std::cout << ' ';     
					break;  
				case 'w':   
					std::cout << "world";    
					break;  
				case '!':   
					std::cout << '!';     
					break;  
				case 'n':   
					std::cout << std::endl;   
					break;  
				default:    
					throw std::runtime_error("Unknown command"); 
					break;
				}  
			}  
		}  
	};

	void InterpretMethod(const std::string& script)  
	{  
		CInterpreter().m_run(script.begin(), script.end());  
	}
}

#endif