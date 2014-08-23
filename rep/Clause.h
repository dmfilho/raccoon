/*
 * Clause.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef CLAUSE_H_
#define CLAUSE_H_

namespace rep {
	class Literal;
	class KB;
}

#include <vector>
#include "Quantifier.h"

using namespace std;

namespace rep {
class Clause {
public:
	/**
	 * The list of literals of the clause.
	 */
	vector<Literal*> literal;

	/**
	 * The list of quantifiers of the clause.
	 */
	vector<Quantifier*> quantifier;

	/**
	 * Concept instance id, C(a) or r(a,...) or -1 if not instantiated.
	 */
	int conceptId;

	/**
	 * Role instance id, r(...,b) or -1 if not instantiated.
	 */
	int roleId;

	/**
	 * Index of the clause on the list of clause of the KB.
	 */
	int idx;

	/**
	 * Knowledge Base of the clause.
	 */
	KB &kb;

	/**
	 * Returns true if clause is empty (i.e. 0 literals and 0 quantifiers)
	 */
	bool empty();

	/**
	 * Sorts the literals of the clause by id and the quantifiers by type,
	 * role id and concept id.
	 */
	void sort();

	/**
	 * Removes a literal from the clause.
	 */
	void removeLiteral(int id);

	/**
	 * Default Constructor
	 */
	Clause(KB& kb);

	/**
	 * Instantiated Concept Constructor
	 */
	Clause(KB& kb, int conceptId);

	/**
	 * Instantiated Role Constructor
	 */
	Clause(KB& kb, int conceptId, int roleId);

	/**
	 * Destructor
	 */
	~Clause();

	void push_literal(Literal* lit);
	void push_quantifier(Quantifier* q);
	void pop_literal(int index);
	void pop_quantifier(int index);
};
}

#endif /* CLAUSE_H_ */
