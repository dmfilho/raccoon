/*
 * Clause.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include "Clause.h"
#include "Concept.h"
#include "Role.h"
#include "Literal.h"
#include "KB.h"
#include "ElementManager.h"
#include <vector>
#include <algorithm>

namespace rep {
Clause::Clause(KB& kb):
conceptId(0),
roleId(0),
idx(0),
kb(kb)
{

}

Clause::Clause(KB& kb, int conceptId):
conceptId(conceptId),
roleId(0),
idx(0),
kb(kb)
{

}

Clause::Clause(KB& kb, int conceptId, int roleId):
conceptId(conceptId),
roleId(roleId),
idx(0),
kb(kb)
{

}

Clause::~Clause() {
	while (literal.size() > 0) {
		delete literal.back();
		literal.pop_back();
	}
	while (quantifier.size() > 0) {
		delete quantifier.back();
		quantifier.pop_back();
	}
}

void Clause::removeLiteral(int id) {
	for (int i = 0, sz = literal.size(); i < sz; i++) {
		if (literal[i]->id == id) {
			swap(literal[i],literal.back());
			literal.pop_back();
			return;
		}
	}
}

bool Clause::empty() {
	return literal.size() == 0 && quantifier.size() == 0;
}

void Clause::sort() {
	std::sort(literal.begin(), literal.end(), [](Literal* a, Literal* b){ return (*a < *b); });
	std::sort(quantifier.begin(), quantifier.end(), [](Quantifier* a, Quantifier* b){ return (*a < *b); });
}

void Clause::push_literal(Literal* lit) {
	kb.element.use(lit->id, this);
	literal.push_back(lit);
}

void Clause::push_quantifier(Quantifier* q) {
	kb.element.use(q->concept->id, this);
	kb.element.use(q->role->id, this);
	quantifier.push_back(q);
}

void Clause::pop_literal(int index) {
	swap(literal[index], literal.back());
	kb.element.disuse(literal.back()->id, this);
	delete literal.back();
	literal.pop_back();
}

void Clause::pop_quantifier(int index) {
	swap(quantifier[index],quantifier.back());
	kb.element.disuse(quantifier.back()->concept->id, this);
	kb.element.disuse(quantifier.back()->role->id, this);
	delete quantifier.back();
	quantifier.pop_back();
}
};
