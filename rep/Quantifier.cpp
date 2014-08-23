/*
 * Quantifier.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include "Quantifier.h"
#include "Literal.h"
#include "Role.h"
#include "Concept.h"
#include <climits>
#include <iostream>

namespace rep {
Quantifier::Quantifier():
universal(0),
role(nullptr),
concept(nullptr)
{

}

Quantifier::Quantifier(bool universal):
universal(universal),
role(nullptr),
concept(nullptr)
{

}

Quantifier::~Quantifier() {
	if (concept != nullptr) delete concept;
	if (role != nullptr) delete role;
}

const bool Quantifier::operator<(const Quantifier& q) const {
	if (q.universal != this->universal) return q.universal;
	int qid = (q.role != nullptr ? q.role->id : INT_MAX);
	int tid = (role != nullptr ? role->id : INT_MAX);
	if (qid != tid) return (tid < qid);
	qid = (q.concept != nullptr ? q.concept->id : INT_MAX);
	tid = (concept != nullptr ? concept->id : INT_MAX);
	return (tid < qid);
}

std::ostream& operator<<(std::ostream& os, const Quantifier& q) {
	if (q.universal) {
		os << "[";
		if (q.role->id >= 0) os << "-";
		os << q.role->name() << " | " << (Literal&)*(q.concept) << "]";
	} else {
		os << "[";
		if (q.role->id < 0) os << "-";
		os << q.role->name() << " & " << (Literal&)*(q.concept) << "]";
	}
	return os;
}
};
