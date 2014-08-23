/*
 * ASTNodeType.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ASTNODETYPE_H_
#define ASTNODETYPE_H_
namespace ast {
enum NodeType {
	// ABox
	ConceptAssertion = 0,
	RoleAssertion = 1,
	// TBox
	Concept = 2,
	Role = 3,
	All = 4,
	Some = 5,
	Conjunction = 6,
	Disjunction = 7,
	Negation = 8,
	Inclusion = 9,
	Equivalence = 10,
	Instance = 11
};
};
#endif /* ASTNODETYPE_H_ */
