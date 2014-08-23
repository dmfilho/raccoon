/*
 * Concept.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include "Literal.h"
#include "ElementManager.h"
#include "Concept.h"

using namespace std;

namespace rep {
Concept::Concept(element::Manager* em):
Literal(em, 0)
{

}

Concept::Concept(element::Manager* em, int id):
Literal(em, id)
{

}

Concept::~Concept() {

}
};
