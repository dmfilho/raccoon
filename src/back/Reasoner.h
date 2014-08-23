/*
 * Reasoner.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef REASONER_H_
#define REASONER_H_

namespace ast {
	class Node;
}
namespace rep {
	class Realization;
	class KB;
}


namespace back {

class Reasoner {
public:
	virtual ast::Node* Classification(rep::KB& kb);
	virtual bool Consistency(rep::KB& kb);
	virtual rep::Realization* Realization(rep::KB& kb);
	virtual ~Reasoner();
};

} /* namespace back */

#endif /* REASONER_H_ */
