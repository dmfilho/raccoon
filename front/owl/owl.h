/*
 * owl.h
 *
 *  Created on: Apr 14, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef OWL_H_
#define OWL_H_

#include "../Parser.h"
#include <string>

namespace rep {
	class KB;
}

namespace front {

class Owl : public Parser {
private:
	int line;
public:
	virtual void parse(std::string& text, rep::KB& kb);
	Owl();
	virtual ~Owl();
};

} /* namespace front */

#endif /* OWL_H_ */
