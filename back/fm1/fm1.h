/*
 * Cdl1.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef FM1_H_
#define FM1_H_

#include "../Reasoner.h"
#include <vector>

namespace rep {
	class KB;
	class Clause;
	class Literal;
}
namespace back {
	class Path;
}

namespace back {

class fm1 : public Reasoner {
private:
	rep::KB* kb;
	bool Consistency(rep::Clause* c, unsigned int row, int cinst, int rinst);
	Path& path;
public:
	//virtual ast::Node* Classification(rep::KB& kb);
	virtual bool Consistency(rep::KB& kb);
	//virtual rep::Realization* Realization(rep::KB& kb);
	fm1();
	virtual ~fm1();
};

} /* namespace back */

#endif /* FM1_H_ */
