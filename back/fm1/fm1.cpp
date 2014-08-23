/*
 * Cdl1.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#include "fm1.h"
#include "../../ast/Node.h"
#include "../../rep/KB.h"
#include "../../rep/Literal.h"
#include "../../rep/Quantifier.h"
#include "../../rep/Clause.h"
#include "../../rep/ElementManager.h"
#include "../../rep/Literal.h"
#include "../../rep/Role.h"
#include "../../rep/Concept.h"
#include "../Path.h"

using namespace rep;

namespace back {
	fm1::~fm1() { delete &path; }
	fm1::fm1(): kb(nullptr), path(*new Path(nullptr)) { }

	#define PROVE_NEXT_AND_RETURN { \
		bool res = Consistency(c, row+1, cinst, rinst); \
		path.restore(); \
		return res; \
	}

	bool fm1::Consistency(rep::Clause* c, unsigned int row, int cinst, int rinst) {
		int rowq, ocinst = cinst, orinst = rinst;
		path.save();
		// Check instances
		if (c->conceptId != 0) {
			if (cinst != 0) {
				if (c->conceptId != cinst) {
					path.restore();
					return false;
				}
			}
			else cinst = c->conceptId;
			path.setLastCinst(cinst);
		}
		if (c->roleId != 0) {
			if (rinst != 0) {
				if (c->roleId != rinst) {
					path.restore();
					return false;
				}
			}
			else rinst = c->roleId;
			path.setLastRinst(rinst);
		}
		// Try every connection of every literal
		rowq = row - c->literal.size();
		if (rowq < 0) {
			int id = c->literal[row]->id;
			int pid = (id < 0 ? -id : id);
			cout << "PROVE: " << kb->element.name[pid] << " PATH: | " << path << endl;
			if (path.has(-id, cinst, rinst, nullptr)) return true; // Reduction
			if (path.has(id, cinst, rinst, c)) return false; // Block-rule
			path.push(id, cinst, rinst, c);
			vector<Clause*>* conn = kb->element.connections(id);
			for (Clause* cc: *conn) {
				if (Consistency(cc, 0, cinst, rinst)) {
					cinst = path.getLastCinst();
					rinst = path.getLastRinst();
					path.pop();
					bool res = Consistency(c, row+1, cinst, rinst);
					if (res) {
						path.restore();
						return true;
					}
					cinst = ocinst;
					rinst = orinst;
					path.push(id, cinst, rinst, c);
				}
			}
			path.pop();
			return false;
		} else if (c->quantifier.size() > (unsigned int)rowq) {
			Quantifier &q = *c->quantifier[rowq];
			if (q.universal) { // check role OR concept
				int id = q.role->id;
				int pid = (id < 0 ? -id : id);
				cout << "PROVE: " << kb->element.name[pid] << " PATH: | " << path << endl;
				if (path.has(-id, cinst, rinst, nullptr)) return true; // Reduction
				if (path.has(id, cinst, rinst, c)) return false; // Block-rule
				path.push(id, cinst, rinst, c);
				vector<Clause*>* conn = kb->element.connections(id);
				for (Clause* cc: *conn) {
					if (Consistency(cc, 0, cinst, rinst)) {
						path.pop();
						bool res = Consistency(c, row+1, cinst, rinst);
						if (res) {
							path.restore();
							return true;
						}
						path.push(id, cinst, rinst, c);
					}
				}
				path.pop();
				id = q.concept->id;
				pid = (id < 0 ? -id : id);
				cout << "PROVE: " << kb->element.name[pid] << " PATH: | " << path << endl;
				if (path.has(-id, 0, 0, nullptr)) return true; // Reduction
				if (path.has(id, 0, 0, c)) return false; // Block-rule
				path.push(id, 0, 0, c);
				conn = kb->element.connections(id);
				for (Clause* cc: *conn) {
					if (Consistency(cc, 0, 0, 0)) {
						path.pop();
						bool res = Consistency(c, row+1, cinst, rinst);
						if (res) {
							path.restore();
							return true;
						}
						path.push(id, 0, 0, c);
					}
				}
				path.pop();
				return false;
			} else { // check role AND concept
				int id = q.role->id;
				int pid = (id < 0 ? -id : id);
				cout << "PROVE: " << kb->element.name[pid] << " PATH: | " << path << endl;
				if (path.has(-id, cinst, rinst, nullptr)) return true; // Reduction
				if (path.has(id, cinst, rinst, c)) return false; // Block-rule
				path.push(id, cinst, rinst, c);
				vector<Clause*>* conn = kb->element.connections(id);
				for (Clause* cc: *conn) {
					if (Consistency(cc, 0, cinst, rinst)) {
						cinst = path.getLastCinst();
						rinst = path.getLastRinst();
						path.pop();
						bool res = Consistency(c, row+1, cinst, rinst);
						if (res) {
							id = q.concept->id;
							pid = (id < 0 ? -id : id);
							cout << "PROVE: " << kb->element.name[pid] << " PATH: | " << path << endl;
							if (path.has(-id, rinst, 0, nullptr)) return true; // Reduction
							if (path.has(id, rinst, 0, c)) return false; // Block-rule
							path.push(id, rinst, 0, c);
							vector<Clause*>* conn = kb->element.connections(id);
							for (Clause* cc: *conn) {
								if (Consistency(cc, 0, rinst, 0)) {
									path.pop();
									bool res = Consistency(c, row+1, cinst, rinst);
									if (res) {
										path.restore();
										return true;
									}
									path.push(id, rinst, 0, c);
								}
							}
							path.pop();
							path.restore();
							return false;
						}
						cinst = ocinst;
						rinst = orinst;
						path.push(id, cinst, rinst, c);
					}
				}
				path.pop();
				return false;
			}
			return false;
		}
		return true;
	}

	bool fm1::Consistency(rep::KB& kb) {
		// start rule
		this->path.em = &kb.element;
		this->kb = &kb;
		int seq = 0;
		for (Clause* c: kb.clause) {
			seq++;
			if (Consistency(c,0,c->conceptId, c->roleId) == true) {
				cout << seq << endl;
				return false;
			}
		}
		return true;
	}
} /* namespace back */
