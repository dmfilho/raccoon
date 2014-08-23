/*
 * Reasoner.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Dimas Melo Filho
 */

#include "Reasoner.h"
#include "../ast/Node.h"
#include "../rep/KB.h"
#include "../exceptions/MethodNotImplemented.h"

namespace back {

	Reasoner::~Reasoner() { }

	ast::Node* Reasoner::Classification(rep::KB& kb) {
		throw new MethodNotImplemented();
	}

	bool Reasoner::Consistency(rep::KB& kb) {
		throw new MethodNotImplemented();
	}

	rep::Realization* Reasoner::Realization(rep::KB& kb) {
		throw new MethodNotImplemented();
	}


} /* namespace back */
