/*
 * KB.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef KB_H_
#define KB_H_

#include <vector>
#include <iostream>
#include "../ast/Node.h"

using namespace std;

namespace rep {
	class Role;
	class Concept;
	class Clause;
	namespace element {
		class Manager;
	}
}

namespace rep {
class KB {
protected:
	/**
	 * Adds an axiom to the current clause.
	 */
	bool radd(ast::Node* axiom, bool neg);
	/**
	 * Adds an element of a right disjunction to the current clause.
	 */
	bool dadd(ast::Node* axiom, bool neg);
	/**
	 * Adds an element of a left conjunction to the current clause.
	 */
	bool cadd(ast::Node* axiom, bool neg);
	/**
	 * Adds a replacement Concept for the axiom and adds a new clause for the
	 * new concept. This method is used to create the concept and the new clause
	 * for Rules 4 and 5.
	 */
	bool createConcept(ast::Node* axiom, bool neg);
	/**
	 * Negates conjunctions and disjunctions according to the parameter.
	 */
	void negConjDisj(ast::Node* axiom, bool neg);
	/**
	 * Adds the role of a quantifier.
	 */
	Role* quantifierRole(ast::Node* axiom, bool neg);
	/**
	 * Adds the concept of a quantifier.
	 */
	Concept* quantifierConcept(ast::Node* axiom, bool neg);
	/**
	 * Stack of clauses. provides means to deal with many clauses recursively.
	 * The top of the stack (back of vector) contains the current clause being added.
	 */
	vector<Clause*> cstack;
public:
	/**
	 * Tells if the KB is sorted (see method sort).
	 */
	bool sorted;
	/**
	 * List of clauses (columns) of the knowledge base.
	 */
	vector<Clause*> clause;
	/**
	 * Element mapping from string to id and vice versa.
	 * An element can be a concept, a role or an instance.
	 * Each element is mapped to an unique id.
	 */
	element::Manager& element;
	/**
	 * Add an axiom to the knowledge base.
	 * The axiom will be normalized if necessary.
	 * Warning: this function is destructive, i.e. it changes the ASTNode values and
	 * semantics.
	 */
	bool add(ast::Node* axiom, bool neg);
	/**
	 * Removes a clause from the KB.
	 */
	void remove(int idx);
	void remove(Clause* c);
	/**
	 * Sorts all connections by address, all literals in clauses by id and all
	 * quantifiers in clauses by type, role id and concept id.
	 * This method IS called by reductions before they take place.
	 */
	void sort();
	/**
	 * Printing methods
	 */
	void printCSV(std::ostream& os);
	/**
	 * Constructor
	 */
	KB();
	/**
	 * Destructor
	 */
	virtual ~KB();
};
}

#endif /* KB_H_ */
