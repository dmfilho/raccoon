/*
 * ElementManager.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Dimas Melo Filho
 */

#include <sstream>
#include <iostream>
#include <algorithm>
#include "ElementManager.h"
#include "Role.h"
#include "Concept.h"

using namespace std;

namespace rep {
	namespace element {
		Manager::Manager():
		count(0),
		createNext(1) {
			// Add the default elements
			add("@NULL", Type::Concept);		// The null element (used to fill the id 0)
			add("$T", Type::Concept);		// The top element
			add("$B", Type::Concept);		// The bottom element
		}

		Manager::~Manager() {
			cout << "Manager::~Manager" << endl;
			for (vector<Clause*>* c: posConnections) if (c != nullptr) delete c;
			for (vector<Clause*>* c: negConnections) if (c != nullptr) delete c;
		}

		int Manager::add(const string& element, Type type) {
			int& elementId = id[element];
			stringstream s;
			switch (type) {
			case Type::Role:
				s << "@r" << element;
				break;
			case Type::Instance:
				s << "@i" << element;
				break;
			case Type::NewConcept:
				s << "@n" << element;
				break;
			default:
				s << element;
				break;
			}
			if (elementId == 0) {
				elementId = count;
				name.push_back(s.str());
				posConnections.push_back(new vector<Clause*>());
				negConnections.push_back(new vector<Clause*>());
				posUse.push_back(0);
				negUse.push_back(0);
				return count++;
			} else return elementId;
		}

		int Manager::add(const char* element, Type type) {
			string str = element;
			return add(str, type);
		}

		int Manager::create() {
			stringstream s;
			s << createNext++;
			return add(s.str(), Type::NewConcept);
		}

		void Manager::use(int id, Clause* clause) {
			if (id > 0) {
				posUse[id]++;
				posConnections[id]->push_back(clause);
			} else if (id < 0) {
				negUse[-id]++;
				negConnections[-id]->push_back(clause);
			}
		}

		void Manager::disuse(int id, Clause* clause) {
			if (id > 0) {
				posUse[id]--;
				vector<Clause*>& clauses = *posConnections[id];
				for (int i = 0, sz = clauses.size(); i < sz; i++) {
					if (clauses[i] == clause) {
						swap(clauses[i], clauses.back());
						clauses.pop_back();
						return;
					}
				}
			} else if (id < 0) {
				negUse[-id]--;
				vector<Clause*>& clauses = *negConnections[-id];
				for (int i = 0, sz = clauses.size(); i < sz; i++) {
					if (clauses[i] == clause) {
						swap(clauses[i], clauses.back());
						clauses.pop_back();
						return;
					}
				}
			}
		}

		string& Manager::operator[](int idx) {
			return name[idx];
		}

		void Manager::sort() {
			for (int i = 0; i < count; i++) {
				std::sort(posConnections[i]->begin(),posConnections[i]->end());
				std::sort(negConnections[i]->begin(),negConnections[i]->end());
			}
		}

		void Manager::removeClause(Clause* c) {
			for (Literal* l: c->literal) disuse(l->id, c);
			for (Quantifier* q: c->quantifier) {
				disuse(q->concept->id, c);
				disuse(q->role->id, c);
			}
		}

		vector<Clause*>* Manager::connections(int id) {
			return (id < 0 ? posConnections[-id] : negConnections[id]);
		}

	}
}


