/*
 * DifferentTypeExpected.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Dimas Melo Filho
 */

#include "DifferentTypeExpected.h"

DifferentTypeExpected::DifferentTypeExpected(ast::NodeType expected, ast::NodeType found):
expected(expected),
found(found)
{

}

DifferentTypeExpected::~DifferentTypeExpected() throw () {

}

