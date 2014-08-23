/*
 * Path.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#include "Path.h"
#include "../rep/Clause.h"
#include "../rep/ElementManager.h"

using namespace std;

namespace back {
	Path::Path(rep::element::Manager* em):
	em(em) { }

	void Path::push(int id, int cinst, int rinst, rep::Clause* clause) {
		this->id.push_back(id);
		this->cinst.push_back(cinst);
		this->rinst.push_back(rinst);
		this->clause.push_back(clause);
	}
	void Path::pop() {
		this->id.pop_back();
		this->cinst.pop_back();
		this->rinst.pop_back();
		this->clause.pop_back();
	}
	bool Path::has(int i, int c, int r, rep::Clause* cl) {
		for (unsigned int z = 0; z < id.size(); z++)
			if (id[z] == i && (c == 0 || cinst[z] == c) && (r == 0 || rinst[z] == r) && (cl == nullptr || cl == clause[z])) return true;
		return false;
	}
	void Path::save() {
		cout << "PATH::SAVE " << cinst.size() << " " << rinst.size() << endl;
		if (cinst.size() == 0 || rinst.size() == 0) return;
		backup.push_back(cinst[cinst.size()-1]);
		backup.push_back(rinst[rinst.size()-1]);
	}
	void Path::setLastCinst(int c) {
		if (cinst.size() == 0) return;
		cinst[cinst.size()-1] = c;
	}
	void Path::setLastRinst(int r) {
		if (rinst.size() == 0) return;
		rinst[rinst.size()-1] = r;
	}
	int Path::getLastCinst() {
		if (cinst.size() == 0) return 0;
		return cinst[cinst.size()-1];
	}
	int Path::getLastRinst() {
		if (rinst.size() == 0) return 0;
		return rinst[rinst.size()-1];
	}

	void Path::restore() {
		if (backup.size() < 2 || rinst.size() < 1 || cinst.size() < 1) return;
		cout << "PATH::RESTORE " << rinst.size() << " " << cinst.size() << endl;
		rinst[rinst.size()-1] = backup.back(); backup.pop_back();
		cinst[cinst.size()-1] = backup.back(); backup.pop_back();
	}

	std::ostream& operator<<(std::ostream& os, const Path& p) {
		for (unsigned int i = 0; i < p.id.size(); i++) {
			int pid = (p.id[i] >= 0 ? p.id[i] : -p.id[i]);
			os << p.em->name[pid];
			if (p.cinst[i] != 0 || p.rinst[i] != 0) {
				os << "(";
				if (p.cinst[i] != 0) os << p.cinst[i];
				if (p.rinst[i] != 0) os << "," << p.rinst[i];
				os << ")";
			}
			os << " | ";
		}
		return os;
	}

} /* namespace back */
