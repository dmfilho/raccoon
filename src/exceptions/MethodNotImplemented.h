/*
 * MethodNotImplemented.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef METHODNOTIMPLEMENTED_H_
#define METHODNOTIMPLEMENTED_H_

#include <exception>

class MethodNotImplemented : public std::exception {
public:
	MethodNotImplemented();
	virtual ~MethodNotImplemented() throw ();
};

#endif /* METHODNOTIMPLEMENTED_H_ */
