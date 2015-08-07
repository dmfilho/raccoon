#ifndef __RACCOON_EXCEPTIONS_UNSUPPORTED_FEATURE_EXCEPTION_H
#define __RACCOON_EXCEPTIONS_UNSUPPORTED_FEATURE_EXCEPTION_H

#include <exception>

namespace raccoon
{
	class unsupported_feature_exception 
	 : public std::exception
	{
	private:
		const char* message;
		const char* feature_name;
	public:
		explicit unsupported_feature_exception(const char* message, const char* feature_name)
		 : message(message)
		 , feature_name(feature_name)
		{
		}
		
		virtual ~unsupported_feature_exception() throw()
		{
		}

		virtual const char* what() const throw()
		{
			return message;
		}
		
		virtual const char* feature() const throw()
		{
			return feature_name;
		}
	};

}

#endif // __RACCOON_EXCEPTIONS_UNSUPPORTED_FEATURE_EXCEPTION_H
