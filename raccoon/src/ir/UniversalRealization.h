/**
 * raccoon, (Rac)iocinador baseado em (Co)nexões para (On)tologias
 * 			Connection based Reasoner for Ontologies
 * 
 * Copyright (C) 2015 Dimas Melo Filho
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 
 * 
 * The author can be reached by e-mail: dldmf@cin.ufpe.br.
 * 
 * \author Dimas Melo Filho <dldmf@cin.ufpe.br>
 * \date 2015-02-28
 * \file
 * This file contains the declaration of the UniversalRealization class.
 */

#ifndef __RACCOON_IR_UNIVERSALREALIZATION_H
#define __RACCOON_IR_UNIVERSALREALIZATION_H

// stl
#include <vector>
// raccoon
#include "Instance.h"
#include "ILiteralRealization.h" // Base class: raccoon::ILiteralRealization
#include "RoleRealization.h"
#include "ConceptRealization.h"

namespace raccoon
{
	class UniversalRealization 
	 : public raccoon::ILiteralRealization
	{
	public:
		/**
		 * This is the value returned by the UniversalRealization::type() method.
		 */
		const int TYPE = 3;
		
		/**
		 * The realization that represents the role of the universal quantifier.
		 */
		RoleRealization role;
		
		/**
		 * The realization that represents the concept of the universal quantifier.
		 */
		ConceptRealization concept;
		
		/**
		 * \brief Constructor
		 */
		UniversalRealization(Literal& role, unsigned int var1r, unsigned int var2r, bool negr, Literal& concept, bool negc);
		
		/**
		 * \brief Destructor. Currently does nothing.
		 */
		~UniversalRealization();

		/**
		 * Implementation of the ILiteralRealization::type method.
		 * \returns the same unique integer for all objects of this class.
		 */
		virtual int type();
		
		/**
		 * \returns true when the literal is negated.
		 */
		virtual bool negated();
		
		/**
		 * Implementation of the ILiteralRealization::complementOf method.
		 * \returns true when the given ILiteralRealization is the complement of this one.
		 */
		virtual bool complementOf(ILiteralRealization* L);
		
		/**
		 * Implementation of the ILiteralRealization::equivalentTo method.
		 * \returns true when the given ILiteralRealization is equivalent to this one.
		 */
		virtual bool equivalentTo(ILiteralRealization* L);
		
		/**
		 * Prints the role, its sign and variable, and the concept, its sign and variable.
		 */
		virtual void print(std::vector<Instance*>& values);
	};

}

#endif // __RACCOON_IR_UNIVERSALREALIZATION_H
