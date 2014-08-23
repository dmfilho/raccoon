/*
 * ASTNode.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#include "Node.h"
#include <iostream>

namespace ast {

Node::Node():
type(NodeType::Instance),
left(nullptr),
right(nullptr) { }

Node::Node(NodeType type):
type(type),
left(nullptr),
right(nullptr) { }

Node::Node(NodeType type, Node* left):
type(type),
left(left),
right(nullptr) { }

Node::Node(NodeType type, Node* left, Node* right):
type(type),
left(left),
right(right) { }

Node::~Node() {
#ifdef _DEBUG
	std::cout << "Node::~Node() This:" << this << " Type:" << type << " Left:" << left << " Right:" << right << endl;
#endif
	switch (type) {
	case NodeType::Concept:
	case NodeType::Role:
	case NodeType::ConceptAssertion:
	case NodeType::RoleAssertion:
		if (left != nullptr) delete (string*) left;
		if (right != nullptr) delete right;
		break;
	case NodeType::Instance:
		if (left != nullptr) delete (string*) left;
		if (right != nullptr) delete (string*) right;
		break;
	default:
		if (left != nullptr) delete left;
		if (right != nullptr) delete right;
		break;
	}
}

};
