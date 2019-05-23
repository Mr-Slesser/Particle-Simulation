#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

namespace Exception
{
    class Example : public std::exception
    {
	    const char* msg;
    
    public:
    	Example(const char* msg)
            : msg(msg) {}
        
        const char* what() {
            return msg;
        }
    };
} // Exception


#endif /* EXCEPTION_HPP */
