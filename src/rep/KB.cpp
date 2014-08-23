/*
 * KB.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include <utility>
#include <sstream>
#include "KB.h"
#include "Quantifier.h"
#include "ElementManager.h"
#include "Role.h"
#include "Concept.h"
#include "Clause.h"
#include "../ast/Node.h"
#include "../ast/NodeType.h"
#include "../exceptions/DifferentTypeExpected.h"

using namespace std;

namespace rep {

KB::KB():
sorted(false),
element(*new element::Manager())
{

}

KB::~KB() {
	cout << "KB::~KB" << endl;
	delete &element;
	for (Clause* c: clause)
		delete c;
}

bool KB::add(ast::Node* axiom, bool neg) {
	cstack.push_back(new Clause(*this));
	if (radd(axiom, neg)) {
		cstack.back()->idx = clause.size();
		clause.push_back(cstack.back());
		cstack.pop_back();
		return true;
	} else {
		delete cstack.back();
		cstack.pop_back();
		return false;
	}
}

bool KB::radd(ast::Node* axiom, bool neg) {
	int id = 0;
	ast::Node* temp1, temp2;
	switch (axiom->type) {
	case ast::NodeType::ConceptAssertion: {
		id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Concept);
		if (neg) id = -id;
		Concept *c = new Concept(&element, id);
		Clause *a = cstack.back();
		a->push_literal(c);
		axiom = axiom->right;
		id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Instance);
		a->conceptId = id;
		return true;
	}
	case ast::NodeType::RoleAssertion: {
		id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Concept);
		if (neg) id = -id;
		Concept *c = new Concept(&element, id);
		Clause *a = cstack.back();
		a->push_literal(c);
		axiom = axiom->right;
		id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Instance);
		a->conceptId = id;
		id = element.add(*reinterpret_cast<string*>(axiom->right), element::Type::Instance);
		return true;
	}
	case ast::NodeType::Concept: {
		id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Concept);
		if (neg) id = -id;
		Concept *c = new Concept(&element, id);
		cstack.back()->push_literal(c);
		return true;
	}
	case ast::NodeType::Role:
		// there should be no lone roles as parts of axioms.
		return false;
	case ast::NodeType::All: {
		// There is no break because All is just absolute the negation of Some
		Quantifier *q = new Quantifier(!neg); // if neg = true, then is universal
		q->role = quantifierRole(axiom->left, !neg);
		cout << "RoleAlloc " << q->role << endl;
		q->concept = quantifierConcept(axiom->right, neg);
		cstack.back()->push_quantifier(q);
		return true;
	}
	case ast::NodeType::Some: {
		Quantifier *q = new Quantifier(neg); // if neg = true, then is universal
		q->role = quantifierRole(axiom->left, neg);
		cout << "RoleAlloc " << q->role << endl;
		q->concept = quantifierConcept(axiom->right, neg);
		cstack.back()->push_quantifier(q);
		return true;
	}
	case ast::NodeType::Conjunction:
		// This case is supposed to be called only for the left side conjunctions
		// which are the accepted normal frm.
		return (cadd(axiom->left, neg) | cadd(axiom->right, neg));
	case ast::NodeType::Disjunction:
		// This case is supposed to be called only for the right side disjunctions
		// which are the accepted normal form.
		return (dadd(axiom->left, neg) | dadd(axiom->right, neg));
	case ast::NodeType::Negation:
		// The negation only inverts the neg parameter, which is used on the above
		// cases.
		do {
			neg = !neg;
			axiom = axiom->left;
		} while (axiom->type == ast::NodeType::Negation);
		return radd(axiom, neg);
	case ast::NodeType::Inclusion:
		// Normalization Rule 2
		// D0 | D1 < A  # D0 < A, D1 < A
		if (axiom->left->type == ast::NodeType::Disjunction) {
			temp1 = axiom->left;
			axiom->left = temp1->left;
			add(axiom,neg);
			axiom->left = temp1->right;
			add(axiom,neg);
			return false;
		}
		// Normalization Rule 3
		// A < C0 & C1 # A < C0, A < C1
		else if (axiom->right->type == ast::NodeType::Conjunction) {
			temp1 = axiom->right;
			axiom->right = temp1->left;
			add(axiom,neg);
			axiom->right = temp1->right;
			add(axiom,neg);
			axiom->right = temp1;
			return false;
		}
		// if the code reached this point, the left and right sides of the
		// inclusion are accepted. They are either: conj(left), disj(right),
		// some, all, and these are treated by the other cases in this switch.
		else {
			return (radd(axiom->left,!neg) | radd(axiom->right,neg));
		}
	case ast::NodeType::Equivalence:
		// Normalization Rule 1
		// A = B  # A < B, B < A
		axiom->type = ast::NodeType::Inclusion;
		add(axiom,neg);
		swap(axiom->left, axiom->right);
		add(axiom,neg);
		swap(axiom->left, axiom->right);
		return false;
	case ast::NodeType::Instance:
		return false;
	default:
		return false;
	}
}

bool KB::dadd(ast::Node* axiom, bool neg) {
	negConjDisj(axiom, neg);
	if (axiom->type == ast::NodeType::Conjunction)
		return createConcept(axiom, neg);
	else if (axiom->type == ast::NodeType::Disjunction)
		return (dadd(axiom->left,neg) | dadd(axiom->right,neg));
	else
		return radd(axiom, neg);
}

bool KB::cadd(ast::Node* axiom, bool neg) {
	negConjDisj(axiom, neg);
	if (axiom->type == ast::NodeType::Disjunction)
		return createConcept(axiom, neg);
	else if (axiom->type == ast::NodeType::Conjunction)
		return (cadd(axiom->left,neg) | cadd(axiom->right,neg));
	else
		return radd(axiom, neg);
}

void KB::negConjDisj(ast::Node* axiom, bool neg) {
	if (neg) {
		if (axiom->type == ast::NodeType::Disjunction)
			axiom->type = ast::NodeType::Conjunction;
		else if (axiom->type == ast::NodeType::Conjunction)
			axiom->type = ast::NodeType::Disjunction;
	}
}

bool KB::createConcept(ast::Node* axiom, bool neg) {
	ast::Node* inclusion = new ast::Node(ast::NodeType::Inclusion);
	inclusion->left = axiom;
	inclusion->right = new ast::Node(ast::NodeType::Concept, reinterpret_cast<ast::Node*>(new string(element[element.create()])) );;
	radd(inclusion->right, neg);
	add(inclusion, !neg);
	inclusion->left = nullptr;
	delete inclusion;
	return true;
}

Role* KB::quantifierRole(ast::Node* axiom, bool neg) {
	if (axiom->type != ast::NodeType::Role)
		throw new DifferentTypeExpected(ast::NodeType::Role, axiom->type);
	stringstream s;
	// Internally, role names start with an @r to differ from concepts.
	int id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Role);
	if (neg) id = -id;
	return new Role(&element, id);
}

Concept* KB::quantifierConcept(ast::Node* axiom, bool neg) {
	// Process negations before processing the quantifier concept
	if (axiom->type == ast::NodeType::Negation) {
		do {
			neg = !neg;
			axiom = axiom->left;
		} while (axiom->type == ast::NodeType::Negation);
	}
	// If it is a concept, create it and return it.
	if (axiom->type == ast::NodeType::Concept) {
		int id = element.add(*reinterpret_cast<string*>(axiom->left), element::Type::Concept);
		if (neg) id = -id;
		return new Concept(&element, id);
	}
	// If not a concept, create a new concept and a new axiom for the concept.
	else {
		int id = element.create();
		ast::Node* inclusion = new ast::Node(ast::NodeType::Inclusion);
		inclusion->left = new ast::Node(ast::NodeType::Concept, reinterpret_cast<ast::Node*>(new string(element[id])));
		if (neg) id = -id;
		Concept* c = new Concept(&element, -id);
		inclusion->right = axiom;
		if (neg) {
			swap(inclusion->left, inclusion->right);
			add(inclusion, neg);
			inclusion->left = nullptr;
		} else {
			add(inclusion, neg);
			inclusion->right = nullptr;
		}
		delete inclusion;
		return c;
	}
}

void KB::sort() {
	if (!sorted) {
		element.sort();
		for (Clause* c: clause) c->sort();
		sorted = true;
	}
}

void KB::remove(int idx) {
	Clause* c = clause[idx];
	// Remove from elementmanager and delete
	element.removeClause(c);
	delete c;
	// Swap and pop
	swap(clause[idx], clause.back());
	clause.pop_back();
	// Redefine the idx of the clause to its new position
	clause[idx]->idx = idx;
}

void KB::remove(Clause* c) {
	remove(c->idx);
}

void KB::printCSV(std::ostream& os) {
	unsigned int row = 0;
	bool rowExists = false;
	stringstream s;
	for (Clause *c: clause) {
		cout << "Clause LITS=" << c->literal.size() << " QUANTS=" << c->quantifier.size() << endl;
	}
	do {
		s.clear();
		s.str(std::string());
		rowExists = false;
		for (Clause* c: clause) {
			unsigned int lsize = c->literal.size();
			if (lsize > row) {
				s << *(c->literal[row]);
				if (c->conceptId != 0) {
					s << "(" << c->kb.element[c->conceptId];
					if (c->roleId != 0) s << "," << c->kb.element[c->roleId];
					s << ")";
				}
				rowExists = true;
			} else if ((lsize = (row - lsize)) < c->quantifier.size()) {
				s << *(c->quantifier[lsize]);
				rowExists = true;
			}
			s << ";";
		}
		s << "\n";
		if (!rowExists) break;
		os << s.str() << flush;
		row++;

	} while (true);
}
}
