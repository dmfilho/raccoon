/*
 * Role.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include "Literal.h"
#include "ElementManager.h"
#include "Role.h"

namespace rep {
Role::Role(element::Manager* em):
Literal(em, 0)
{

}

Role::Role(element::Manager* em, int id):
Literal(em, id)
{

}

Role::~Role() {

}
};
