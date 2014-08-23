/*
 * Path.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <iostream>

namespace rep {
	class Clause;
	namespace element {
		class Manager;
	}
}

using namespace std;

namespace back {

class Path {
public:
	vector<int> id;
	vector<int> cinst;
	vector<int> rinst;
	vector<int> backup;
	vector<rep::Clause*> clause;
	rep::element::Manager* em;

	Path(rep::element::Manager* em);
	void push(int id, int cinst, int rinst, rep::Clause* clause);
	void pop();
	bool has(int id, int cinst, int rinst, rep::Clause* clause);
	void setLastCinst(int c);
	int getLastCinst();
	void setLastRinst(int r);
	int getLastRinst();
	void restore();
	void save();
	friend std::ostream& operator<<(std::ostream& os, const Path& p);
};

} /* namespace back */

#endif /* PATH_H_ */
