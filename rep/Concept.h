/*
 * Literal.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef LITERAL_H_
#define LITERAL_H_

#include "Literal.h"

namespace rep {
	namespace element {
		class Manager;
	}
}

namespace rep {
/**
 * This class defines a concept, a kind of literal that is contained in clauses.
 * The concept class can't handle any instance. Instances are stored on the clause
 * itself.
 */
class Concept : public Literal {
public:
	/**
	 * Constructor with id = 0.
	 */
	Concept(element::Manager* em);
	/**
	 * Constructor that initializes the id
	 */
	Concept(element::Manager* em, int id);
	/**
	 * Destructor
	 */
	virtual ~Concept();
};
};

#endif /* LITERAL_H_ */
