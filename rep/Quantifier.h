/*
 * Quantifier.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef QUANTIFIER_H_
#define QUANTIFIER_H_

namespace rep {
	class Role;
	class Concept;
}

#include <string>

namespace rep {
	class Quantifier {
	public:
		/**
		 * Defines the type of quantifier. True for universal, false for existential.
		 */
		bool universal;
		/**
		 * The quantifier's role
		 */
		Role *role;
		/**
		 * The quantifier's concept
		 */
		Concept *concept;
		/**
		 * name method replacement.
		 */
		std::string& name();
		/**
		 * Compare the type (existential < universal), role id, concept id.
		 */
		const bool operator<(const Quantifier& q) const;
		/**
		 * Default Constructor
		 */
		Quantifier();
		/**
		 * Constructor which defines the quantifier type.
		 */
		Quantifier(bool universal);
		/**
		 * Destructor
		 */
		virtual ~Quantifier();
		/**
		 * ostream operator << overload.
		 */
		friend std::ostream& operator<<(std::ostream& os, const Quantifier& q);
	};
}

#endif /* QUANTIFIER_H_ */
