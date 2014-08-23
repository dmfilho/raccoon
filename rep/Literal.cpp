/*
 * Literal.cpp
 * A literal defines the base class for concepts and roles.
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include <vector>
#include <iostream>
#include "Clause.h"
#include "ElementManager.h"
#include "Literal.h"

namespace rep {
Literal::Literal(element::Manager* em, int id):
em(em),
id(id)
{

}

Literal::~Literal()
{

}

vector<Clause*>* Literal::connections() {
	if (id < 0) return em->posConnections[-id];
	else return em->negConnections[id];
}

const string& Literal::name() const {
	return em->name[id < 0 ? -id : id];
}

const bool Literal::operator<(const Literal& lit) const {
	return (this->id < lit.id);
}

std::ostream& operator<<(std::ostream& os, const Literal& c) {
	if (c.id < 0) os << "-";
	os << c.name();
	return os;
}
};
