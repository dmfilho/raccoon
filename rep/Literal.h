/*
 * Literal.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <vector>
#include <string>

using namespace std;

namespace rep {
	namespace element {
		class Manager;
	}
	class Clause;
}

/**
 * Represents a literal of the clause. It can be either a Concept or a Role.
 */
namespace rep {
class Literal {
protected:
	/**
	 * ElementManager of the knowledge base of the literal.
	 * It is used to retrieve the element name and connections.
	 */
	element::Manager* em;
public:
	/**
	 * Integer ID of the element.
	 * = 0 null (no literal / invalid literal)
	 * > 0 positive literal
	 * < 0 negative literal
	 * e.g. if a=1 then -a=-1.
	 */
	int id;
	/**
	 * Get the list of connections to the element.
	 */
	virtual vector<Clause*>* connections();
	/**
	 * Returns the name (text) of the element.
	 */
	virtual const string& name() const;
	/**
	 * Compare the ids of the Literals.
	 */
	const bool operator<(const Literal& lit) const;
	/**
	 * Constructor that initializes the element manager and the id with an integer.
	 */
	Literal(element::Manager* em, int id);
	/**
	 * Destructor
	 */
	virtual ~Literal();
	/**
	 * ostream operator <<, for printing to cout and other streams.
	 */
	friend std::ostream& operator<<(std::ostream&, const Literal&);
};
};
#endif /* ELEMENT_H_ */
