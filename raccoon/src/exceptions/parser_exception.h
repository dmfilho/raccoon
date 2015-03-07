#ifndef __RACCOON_EXCEPTIONS_PARSER_EXCEPTION_H
#define __RACCOON_EXCEPTIONS_PARSER_EXCEPTION_H

#include <exception>

namespace raccoon
{
	class parser_exception
	 : public std::exception
	{
	private:
		const char* message;
	public:
		explicit parser_exception(const char* message)
		 : message(message)
		{
		}
		
		virtual ~parser_exception() throw()
		{
		}

		virtual const char* what() const throw()
		{
			return message;
		}
	};
}

#endif // __RACCOON_EXCEPTIONS_PARSER_EXCEPTION_H
