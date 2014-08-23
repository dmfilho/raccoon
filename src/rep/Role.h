/*
 * Role.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ROLE_H_
#define ROLE_H_

#include "Literal.h"

namespace rep {
	namespace element {
		class Manager;
	}
}

namespace rep {
	class Role : public Literal {
	public:
		/**
		 * Constructor with id = 0
		 */
		Role(element::Manager* em);
		/**
		 * Constructor that initializes the id.
		 */
		Role(element::Manager* em, int id);
		/**
		 * Destructor
		 */
		virtual ~Role();
	};
}

#endif /* ROLE_H_ */
