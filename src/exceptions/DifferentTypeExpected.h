/*
 * DifferentTypeExpected.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef DIFFERENTTYPEEXPECTED_H_
#define DIFFERENTTYPEEXPECTED_H_

#include <exception>
#include "../ast/NodeType.h"

class DifferentTypeExpected : public std::exception {
public:
	ast::NodeType expected;
	ast::NodeType found;
	DifferentTypeExpected(ast::NodeType expected, ast::NodeType found);
	virtual ~DifferentTypeExpected() throw ();
};

#endif /* DIFFERENTTYPEEXPECTED_H_ */
