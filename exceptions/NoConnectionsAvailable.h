/*
 * NoConnectionsAvailable.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef NOCONNECTIONSAVAILABLE_H_
#define NOCONNECTIONSAVAILABLE_H_

#include <exception>

class NoConnectionsAvailable : public std::exception {
public:
	NoConnectionsAvailable();
	virtual ~NoConnectionsAvailable() throw ();
};

#endif /* NOCONNECTIONSAVAILABLE_H_ */
