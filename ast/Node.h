/*
 * ASTNode.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ASTNODE_H_
#define ASTNODE_H_

#include <string>
#include "NodeType.h"

using namespace std;

namespace ast {

class Node {
public:
	NodeType type;
	Node* left;
	Node* right;
	Node();
	Node(NodeType type);
	Node(NodeType type, Node* left);
	Node(NodeType type, Node* left, Node* right);
	virtual ~Node();
};

};
#endif /* ASTNODE_H_ */
