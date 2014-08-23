/*
 * alc.h
 *
 *  Created on: Apr 15, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ALC_H_
#define ALC_H_

#include "../Parser.h"
#include <vector>
#include <string>

namespace rep {
	class KB;
}
namespace ast {
	class Node;
}

using namespace std;

namespace front {

class Alc : public Parser {
private:
	int lines;
	vector<ast::Node*> nodes;
public:
	void pop(int n);
	virtual void parse(std::string& text, rep::KB& kb);
	virtual void fromFile(const std::string& fileName, rep::KB& kb);
	Alc();
	virtual ~Alc();
};

} /* namespace front */

#endif /* ALC_H_ */
