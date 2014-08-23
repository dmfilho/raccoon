/*
 * Parser.h
 *
 *  Created on: Apr 14, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>

namespace rep {
	class KB;
}

namespace front {

class Parser {
public:
	virtual void parse(std::string& text, rep::KB& kb) = 0;
	virtual ~Parser();
};

} /* namespace front */

#endif /* PARSER_H_ */
